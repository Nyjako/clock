#include <iostream>
#include <chrono>
#include <ostream>
#include <string>
#include "include/Clock.hpp"

int main(int argc, char* argv[]) 
{
    if (argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
        std::cerr << "Usage: " << argv[0] << " <mode> [<duration>]" << std::endl;
        std::cerr << "Modes: " << std::endl;
        std::cerr << "  clock          - Show current system time." << std::endl;
        std::cerr << "  countdown <s>  - Run countdown for <s> seconds." << std::endl;
        std::cerr << "  timer          - Run timer that counts from 0." << std::endl;
        return (argc < 2)? 1 : 0;
    }

    Clock clock;
    std::string mode = argv[1];

    if (mode == "clock") {
        clock.run_clock();
    }
    else if (mode == "countdown") {
        if (argc < 3) {
            std::cerr << "Error: countdown mode requires duration in seconds." << std::endl;
            return 1;
        }
        int duration = std::stoi(argv[2]);
        clock.run_countdown(std::chrono::system_clock::now() + std::chrono::seconds(duration));
    }
    else if (mode == "timer") {
        clock.run_timer();
    }
    else {
        std::cerr << "Error: Unknown mode " << mode << std::endl;
        return 1;
    }

    return 0;
}