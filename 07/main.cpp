#include <iostream>
#include <string>
#include <sstream>
#include "vector.h"
#include "allocator.h"

using namespace std;

int main() {
    Vector<int, Allocator<int>> a;
    Vector<int, Allocator<int>> b(100);
    const Vector<int, Allocator<int>> c{ 1, 2, 3, 4, 3, 2, 1 };

    assert (a.size() == 0 && b.size() == 100 && c.size() == 7);
    cout << "Test 1 passed (size)" << endl;

    a = { 1, 2, 3, 4, 3, 2, 1 };
    b = c;
    assert(a.size() == 7 && b.size() == 7 && b.capacity() == 100);
    cout << "Test 2 passed (=)" << endl;

    a[3] = 10;
    assert (a[0] == a[6] && a[1] == a[5] && a[3] == 10);
    cout << "Test 3 passed ([])" << endl;

    int n = 2;
    a.push_back(0);
    a.push_back(1);
    a.push_back(std::move(n));
    assert(a[7] == 0 && a[8] == 1 && a[9] == 2 && a.capacity() == 14 && a.size() == 10);
    cout << "Test 4 passed (push_back)" << endl;

    a.pop_back();
    a.pop_back();
    a.pop_back();
    assert(a[a.size() - 1] == 1);
    cout << "Test 5 passed (pop_back)" << endl;

    b.resize(100);
    a.resize(50, 1);
    assert(b.capacity() == 100 && a.size() == 50 && a[42] == 1 && b[1] == 2 && a[2] == 3);
    cout << "Test 6 passed (resize)" << endl;

    a.clear();
    assert(a.capacity() == 50 && a.size() == 0 && a.empty());
    cout << "Test 7 passed (clear and empty)" << endl;

    a.reserve(13);
    b.reserve(150000);
    assert(a.capacity() == 50 && b.capacity() == 150000);
    cout << "Test 8 passed (reserve)" << endl;

    stringstream ss;
    a = c;
    a.push_back(0);
    for (auto& i : a)
        ss << i << ' ';
    assert(ss.str() == "1 2 3 4 3 2 1 0 ");
    cout << "Test 9 passed (iterator)" << endl;

    ss.str(std::string());
    for (auto i = a.rbegin(); i < a.rend(); ++i)
        ss << *i << ' ';
    assert(ss.str() == "0 1 2 3 4 3 2 1 ");
    cout << "Test 10 passed (reverse iterator)" << endl;

    assert((a.begin() + a.size() == a.end()) && (a.rbegin() + a.size() == a.rend()) &&
           (a.end() - a.begin() == a.size()));
    cout << "Test 11 passed (iterator operators)" << endl;

    cout << "All 11 tests passed. Success." << endl;
    return 0;
}
