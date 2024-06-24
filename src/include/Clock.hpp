#ifndef CLOCK_H
#define CLOCK_H

#pragma once

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <ostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NUMBER_WIDTH 100
#define NUMBER_HEIGHT 150
#define FACES_NUMBER 4
#define RENDER_DELAY 100


/**
 * @class Clock
 * @brief A class to manage and display time using SDL for rendering.
 * 
 * The Clock class provides functionality to display the current system time,
 * run a countdown timer, and run a stopwatch timer. It uses SDL for creating
 * a window and rendering the time. The class includes methods for preparing
 * the rendering environment, presenting the renderer, and formatting time
 * as strings.
 */
class Clock
{
private:
    SDL_Window *window;           /**< Pointer to the SDL window. */
    SDL_Renderer *renderer;       /**< Pointer to the SDL renderer. */
    SDL_Surface *font;            /**< Pointer to the SDL surface for the font. */
    SDL_Texture *font_tex;        /**< Pointer to the SDL texture for the font. */
    int quit = 0;                 /**< Flag to indicate if the application should quit. */

public:
    /**
     * @brief Constructor for the Clock class.
     */
    Clock();

    /**
     * @brief Destructor for the Clock class.
     */
    ~Clock();

    /**
     * @brief show clock with current system time
     * 
     */
    void run_clock();

    /**
     * @brief Runs countdown
     * 
     * @param end end time
     */
    void run_countdown(const std::chrono::system_clock::time_point& end);

    /**
     * @brief Runs timer that count from 0
     * 
     */
    void run_timer();

private:
    /**
     * @brief Check for quit event and clear canvas
     * 
     */
    void prepare();

    /**
     * @brief present renderer and sleep
     * 
     */
    void present();

    /**
     * @brief Get number from font
     * 
     * @param number what number we want to get
     * @param index Index if -1 get random 
     * @return SDL_Rect* Returns rect representing number in font
     */
    SDL_Rect get_number(int number, int index = -1);

    /**
     * @brief write time into renderer
     * 
     * @param time string representing time
     */
    void render_time(std::string time);

    /**
    * @brief Returns current time formated as string HH:MM:SS
    * 
    * @return std::string formated string HH:MM:SS
    */
    std::string getTime();

    /**
     * @brief Returns time formated as string HH:MM:SS
     * 
     * @param timePoint Time point we want to format
     * @return std::string formated string HH:MM:SS
     */
    std::string getTime(const std::chrono::system_clock::time_point& timePoint);

    /**
     * @brief Returns time duration formated as string HH:MM:SS
     * 
     * @param start Time point we want to start from
     * @param end Time point we want to finish
     * @return std::string formated string HH:MM:SS
     */
    std::string getTime(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end);

    /**
     * @brief Convert duration into formated string HH:MM:SS
     * 
     * @param duration 
     * @return std::string 
     */
    std::string getDurationTime(const std::chrono::duration<int64_t>& duration);
};

#endif