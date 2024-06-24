#include "include/Clock.hpp"


Clock::Clock()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Error SDL2 Initialization: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if ( IMG_Init(IMG_INIT_PNG) == 0 ) {
        std::cerr << "Error SDL2_image Initialization";
        exit(EXIT_FAILURE);
    }

    Clock::window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 150, SDL_WINDOW_VULKAN);
    if (!Clock::window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    Clock::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!Clock::renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    Clock::font = IMG_Load("font.png");
    if (!Clock::font) {
        std::cerr << "Failed to load font: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    Clock::font_tex = SDL_CreateTextureFromSurface(renderer, font);
    if (!Clock::font_tex) {
        std::cerr << "Error creating font texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    srand( time(NULL) );
}

Clock::~Clock()
{
    if (font) SDL_FreeSurface(font);
    if (font_tex) SDL_DestroyTexture(font_tex);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

std::string Clock::getTime()
{
    auto now = std::chrono::system_clock::now();
    return Clock::getTime(now);
}

std::string Clock::getTime(const std::chrono::system_clock::time_point& timePoint)
{
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(timePoint);
    std::tm local_time = *std::localtime(&now_time_t);
    
    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << local_time.tm_hour << ':' 
       << std::setw(2) << local_time.tm_min  << ':' 
       << std::setw(2) << local_time.tm_sec;

    return ss.str();
}

std::string Clock::getDurationTime(const std::chrono::duration<int64_t>& duration)
{
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1));
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1));

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << hours.count() << ':' 
       << std::setw(2) << minutes.count() << ':' 
       << std::setw(2) << seconds.count();

    return ss.str();
}

std::string Clock::getTime(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end)
{
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    if (duration.count() > 0) return Clock::getDurationTime( duration );
    else return "00:00:00";
}

SDL_Rect Clock::get_number(int number, int index)
{
    if (index == -1) {
        index = rand() % FACES_NUMBER;
    }

    SDL_Rect out = SDL_Rect{
        .x = number * NUMBER_WIDTH,
        .y = index  * NUMBER_HEIGHT,
        .w = NUMBER_WIDTH,
        .h = NUMBER_HEIGHT
    };

    return out;
}

void Clock::render_time(std::string time)
{
    int counter = 0;
    for (char c : time) {
        SDL_Rect current = Clock::get_number(c - '0');
        SDL_Rect position{
            .x = NUMBER_WIDTH * counter++,
            .y = 0,
            .w = NUMBER_WIDTH, // Limited to size in font for now
            .h = NUMBER_HEIGHT
        };
        SDL_RenderCopy(Clock::renderer, Clock::font_tex, &current, &position);
    }
}

void Clock::prepare()
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) ) {
        switch (event.type) {
            case SDL_QUIT:
                Clock::quit = 1;
                break;
        }
    }

    SDL_SetRenderDrawColor(Clock::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Clock::renderer);     
}

void Clock::present()
{
    SDL_RenderPresent( Clock::renderer );
    SDL_Delay( RENDER_DELAY );
}

void Clock::run_clock()
{
    while (!Clock::quit) {
        Clock::prepare();
        Clock::render_time(Clock::getTime());
        Clock::present();
    }
}

void Clock::run_countdown(const std::chrono::system_clock::time_point& end)
{
    while (!Clock::quit) {
        Clock::prepare();
        Clock::render_time(Clock::getTime(std::chrono::system_clock::now(), end));
        Clock::present();
    }
}

void Clock::run_timer()
{
    auto start_time = std::chrono::system_clock::now();
    while (!Clock::quit) {
        Clock::prepare();
        Clock::render_time(Clock::getTime(start_time, std::chrono::system_clock::now()));
        Clock::present();
    }
}