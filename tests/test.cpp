// Just test to make sure everything builds and tests result are correct

#include <iostream>
#include <cassert>

// Functions to test
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }


void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    std::cout << "  test_add passed!" << std::endl;
}


void test_subtract() {
    assert(subtract(5, 3) == 2);
    assert(subtract(1, 1) == 0);
    assert(subtract(0, 1) == -1);
    std::cout << "  test_subtract passed!" << std::endl;
}


int main() {
    std::cout << "Running tests..." << std::endl;

    test_add();
    test_subtract();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}