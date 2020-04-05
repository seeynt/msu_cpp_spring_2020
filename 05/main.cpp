#include "BigInt.h"
#include <sstream>

std::string BigIntToStr(const BigInt& a) {
    std::stringstream ss;
    ss << a;
    return ss.str();
}

int main() {
    BigInt a = -999999999;
    BigInt b = 1000000000;

    BigInt c = a + b;
    assert(BigIntToStr(c) == "1");
    std::cout << "Test 1 passed (-999999999 + 1000000000 = 1)" << std::endl;

    c = b + a;
    assert(BigIntToStr(c) == "1");
    std::cout << "Test 2 passed (1000000000 - 999999999 = 1)" << std::endl;

    c = a + b + 2 + 3 + 4 + 5;
    assert(BigIntToStr(c) == "15");
    std::cout << "Test 3 passed (a + b + 2 + 3 + 4 + 5 = 15)" << std::endl;

    a = -45;
    b = -b;
    c = a + b;
    assert(BigIntToStr(c) == "-1000000045");
    std::cout << "Test 4 passed (-1000000000 + (-45) = -1000000045)" << std::endl;

    c = a - b;
    assert(BigIntToStr(c) == "999999955");
    std::cout << "Test 5 passed (-45 - (-1000000000) = 999999955)" << std::endl;

    assert(c > a);
    assert(-c > b);
    assert(a == a);
    assert(!(a < a));
    assert(a >= a);
    b = a;
    assert(b <= a);
    assert(a + 2 > b);
    assert(a + 1 != b);
    std::cout << "Test 6 passed (== >= <= > < !=)" << std::endl;

    std::stringstream ss;
    ss << "-0000000000000000000088005553535008800555353500000";
    ss >> c;
    assert(BigIntToStr(c) == "-88005553535008800555353500000");
    std::cout << "Test 7 passed (>> and <<)" << std::endl;

    assert(BigIntToStr(c + 1) == "-88005553535008800555353499999");
    std::cout << "Test 8 passed (BigInt + BigInt)" << std::endl;

    std::cout << "All 8 tests passed. Success." << std::endl;
    return 0;
}
