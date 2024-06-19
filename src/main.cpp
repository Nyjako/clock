#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ostream>

#define NUMBER_WIDTH 100
#define NUMBER_HEIGHT 150
#define FACES_NUMBER 4

std::string getCurrentTime() 
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_time_t);
    
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << local_time.tm_hour << ':' << std::setw(2) << local_time.tm_min << ':' << std::setw(2) << local_time.tm_sec;

    return ss.str();
}

SDL_Rect *get_number(int number, int index = -1) 
{
    if (index == -1) {
        index = rand() % FACES_NUMBER;
    }

    SDL_Rect *out = new SDL_Rect{
        .x = number * NUMBER_WIDTH,
        .y = index  * NUMBER_HEIGHT,
        .w = NUMBER_WIDTH,
        .h = NUMBER_HEIGHT
    };

    return out;
}

void render_time(SDL_Renderer *renderer, SDL_Texture *texture, std::string time)
{
    int counter = 0;
    for (char c : time) {
        SDL_Rect *current = get_number(c - '0');
        SDL_Rect position{
            .x = NUMBER_WIDTH * counter++,
            .y = 0,
            .w = NUMBER_WIDTH, // Limited to size in font for now
            .h = NUMBER_HEIGHT
        };
        SDL_RenderCopy(renderer, texture, current, &position);
    }
}

int main(void) 
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Error SDL2 Initialization: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if ( IMG_Init(IMG_INIT_PNG) == 0 ) {
        std::cerr << "Error SDL2_image Initialization";
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 150, SDL_WINDOW_VULKAN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Surface *font = IMG_Load("font.png");
    if (!font) {
        std::cerr << "Failed to load font: " << IMG_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Texture *font_tex = SDL_CreateTextureFromSurface(renderer, font);
    if (!font_tex) {
        std::cerr << "Error creating font texture" << std::endl;
        return EXIT_FAILURE;
    }

    srand( time(NULL) );

    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while ( SDL_PollEvent(&event) ) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);     

        render_time(renderer, font_tex, getCurrentTime());

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    SDL_FreeSurface(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}