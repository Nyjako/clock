// Just test to make sure everything builds and tests result are correct

#include <iostream>
#include <cassert>

#define SILENT
#include "../src/include/helper.hpp"


// Functions to test
bool isValidNumber(const char* str);
int parse_duration(char* arg);


void test_valid_number() {
    assert( isValidNumber("1")       == true  );
    assert( isValidNumber("100")     == true  );
    assert( isValidNumber("9999")    == true  );
    assert( isValidNumber("")        == false );
    assert( isValidNumber("n")       == false );
    assert( isValidNumber("n1b2f45") == false );

    std::cout << "  test_valid_number passed!" << std::endl;
}


void test_parse_duration() {
    assert( parse_duration("0s") == 0 );
    assert( parse_duration("0S") == 0 );
    assert( parse_duration("1s") == 1 );
    assert( parse_duration("1S") == 1 );
    assert( parse_duration("1m") == 60 );
    assert( parse_duration("1M") == 60 );
    assert( parse_duration("1h") == 3600 );
    assert( parse_duration("1H") == 3600 );
    assert( parse_duration("10s") == 10 );
    assert( parse_duration("10S") == 10 );
    assert( parse_duration("10m") == 600 );
    assert( parse_duration("10M") == 600 );
    assert( parse_duration("10h") == 36000 );
    assert( parse_duration("10H") == 36000 );
    assert( parse_duration("") == 0 );
    assert( parse_duration("1") == 0 );
    assert( parse_duration("10D") == 0 );
    assert( parse_duration("M10") == 0 );

    std::cout << "  test_parse_duration passed!" << std::endl;
}


int main() {
    std::cout << "Running tests..." << std::endl;

    test_valid_number();
    test_parse_duration();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}