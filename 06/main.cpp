#include <iostream>
#include "format.h"

int main() {
    std::string test = format("{1} + {1} = {0}", "two", "one");
    std::cout << test << std::endl;
    assert(test == "one + one = two");

    std::cout << "Test 1 passed" << std::endl;

    test = format("{1} + {1} = {1}", 1, 0);
    assert(test == "0 + 0 = 0");
    std::cout << "Test 2 passed (missing args)" << std::endl;

    try {
        test = format("{1} + {1} = {2}", 1, 0);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 3 passed (missing args)" << std::endl;
    }

    try {
        test = format("{1} + {1} = {5}", 1, 0);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 4 passed (missing args)" << std::endl;
    }

    test = format("{0}{2} = {3}", '-', 0, 100, -100);
    assert(test == "-100 = -100");
    std::cout << "Test 5 passed (excessive args)" << std::endl;

    test = format(test, 0, 2, 34);
    assert(test == "-100 = -100");
    std::cout << "Test 6 passed (excessive args)" << std::endl;

    try {
        test = format("{}", 0);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 7 passed (invalid use of {})" << std::endl;
    }

    try {
        test = format("{", 0, 1);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 8 passed (invalid use of {})" << std::endl;
    }

    try {
        test = format("{-1}", 0, 1);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 9 passed (invalid use of {})" << std::endl;
    }

    try {
        test = format("{0}}", 10);
    }
    catch (std::runtime_error& error) {
        std::cout << "Test 10 passed (invalid use of {})" << std::endl;
    }

    std::cout << "All 10 tests passed. Success." << std::endl;
    return 0;
}
