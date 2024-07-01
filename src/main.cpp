#include <iostream>
#include <chrono>
#include "include/helper.hpp"
#include "include/Clock.hpp"

#ifndef APP_NAME
#define APP_NAME "Clock"
#endif

#ifndef APP_VERSION
#define APP_VERSION "1.0.0"
#endif

void print_help(char* argv0, std::ostream& out)
{
    out << APP_NAME << " Application v" << APP_VERSION << std::endl;
    out << "A simple clock application written in C++ using SDL2, featuring a hand-drawn font." << std::endl;
    out << "Inspired by clock used by [Tsoding](https://www.twitch.tv/tsoding) in his streams." << std::endl;
    out << std::endl;
    out << "GitHub: https://github.com/Nyjako/clock" << std::endl;
    out << std::endl;
    out << "Usage: " << argv0 << " <mode> [<duration>]" << std::endl;
    out << std::endl;
    out << "Modes: " << std::endl;
    out << "  c / clock          - Show current system time." << std::endl;
    out << "  d / countdown <s>  - Run countdown for <duration> seconds, minutes, or hours." << std::endl;
    out << "  t / timer          - Run timer that counts from 0." << std::endl;
    out << std::endl;
    out << "Duration format:" << std::endl;
    out << "  - For seconds: <number>s (e.g., 30s for 30 seconds)" << std::endl;
    out << "  - For minutes: <number>m (e.g., 5m for 5 minutes)" << std::endl;
    out << "  - For hours:   <number>h (e.g., 2h for 2 hours)" << std::endl;
    out << "  - Mix durations: Combine units (e.g., 30s 2m 1h for 1 hour, 2 minutes, and 30 seconds)" << std::endl;
    out << std::endl;
    out << "Commands:" << std::endl;
    out << "  h / help - Show this help message." << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
        print_help(argv[0], (argc < 2)? std::cerr : std::cout);
        return (argc < 2)? 1 : 0;
    }

    Clock clock;
    std::string mode = argv[1];

    if (mode == "clock" || mode == "c") {
        clock.run_clock();
    }
    else if (mode == "countdown" || mode == "d") {
        if (argc < 3) {
            std::cerr << "Error: countdown mode requires duration." << std::endl << std::endl;
            print_help(argv[0], std::cerr);
            return 1;
        }

        int duration = 0;
        for (int i = 0; i < argc - 2; i++) {
            char* curr_arg = argv[i + 2];
            duration += parse_duration(curr_arg);
        }

        clock.run_countdown(std::chrono::system_clock::now() + std::chrono::seconds(duration));
    }
    else if (mode == "timer" || mode == "t") {
        clock.run_timer();
    }
    else {
        std::cerr << "Error: Unknown mode " << mode << std::endl << std::endl;
        print_help(argv[0], std::cerr);
        return 1;
    }

    return 0;
}