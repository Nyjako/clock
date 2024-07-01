#ifndef HELPER_H
#define HELPER_H

#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include <cctype>

bool isValidNumber(const char* str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

int parse_duration(char* arg)
{
    int unit_multiplier = 0;

    if (arg && strlen(arg) > 0) {
        size_t length = strlen(arg);

        if (length < 2) {
            std::cerr << "The input \"" << arg << "\" is too short to be a valid number." << std::endl;
            return 0;
        }

        char unit = arg[length - 1];
        switch (unit) {
            case 'S':
            case 's':
                unit_multiplier = 1;
                break;
            case 'M':
            case 'm':
                unit_multiplier = 60;
                break;
            case 'H':
            case 'h':
                unit_multiplier = 3600;
                break;
            default:
                std::cerr << "Unknown unit '" << unit << '\'' << std::endl;
                return 0;
        }

        char* temp = new char[length];
        strncpy(temp, arg, length - 1);
        temp[length - 1] = '\0'; // Null-terminate the new string

        if (!isValidNumber(temp)) {
            std::cerr << "Number is not valid \"" << temp << '"' << std::endl;
            delete[] temp;
            return 0;
        }

        int number = std::strtol(temp, nullptr, 10);
        delete[] temp;
        return number * unit_multiplier;
    }

    return 0;
}

#endif