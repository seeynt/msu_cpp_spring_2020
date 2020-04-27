#include "pool.h"
#include <iostream>

struct A {};

void a(const A&, int num, std::string str, const char c) {
    std::cout << "Test 1 passed (arguments)" << std::endl;
}

int b(int num) {
    std::cout << "Test " << num << " passed (just function)" << std::endl;
    return 0;
}

int c(int num) {
    return num;
}

std::thread::id d(int num) {
    std::cout << "Test " << num << " passed (queue)" << std::endl;
    return std::this_thread::get_id();
}

int main() {
    ThreadPool pool(4);

    auto task1 = pool.exec(a, A(), 100, "100", '1');
    task1.get();

    auto task2 = pool.exec([]() { std::cout << "Test 2 passed (lambda)" << std::endl; });
    task2.get();

    auto task3 = pool.exec(b, 3);

    assert(task3.get() == 0);
    std::cout << "Test 4 passed (return value)" << std::endl;

    auto task5 = pool.exec(c, 5);
    std::cout << "Test " << task5.get() << " passed (return value)" << std::endl;

    auto task6 = pool.exec(d, 6);

    assert(task6.get() != std::this_thread::get_id());
    std::cout << "Test 7 passed (thread id)" << std::endl;

    std::cout << "All 7 tests passed. Success" << std::endl;
    return 0;
}
