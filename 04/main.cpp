#include <cstring>
#include <sstream>
#include <iostream>
#include "serializer.h"

struct Data {
    uint64_t a;
    bool b;
    bool c;
    uint64_t d;
    uint64_t e;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c, d, e);
    }
};

struct TestData {
	uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b);
    }
};

int main() {
	Data x { 1, false, true, 2, 3 };
	Data y { 0, false, false, 0, 0 };
	TestData z { 100, true };

	std::stringstream streamX;
	std::stringstream streamZ;

	Serializer serializerX(streamX);
	Serializer serializerZ(streamZ);
	serializerX.save(x);
	serializerZ.save(z);

	Deserializer deserializerYZ(streamZ);
	const Error errZ = deserializerYZ.load(y);

	assert(errZ == Error::CorruptedArchive);

	std::cout << "Test 1 passed (corrupted archive)" << std::endl;

	Deserializer deserializerYX(streamX);
	const Error errX = deserializerYX.load(y);

	assert(errX == Error::NoError);

	std::cout << "Test 2 passed (successful load)" << std::endl;

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
	assert(x.d == y.d);
	assert(x.e == y.e);

	std::cout << "Tests 3 - 7 passed (correct load)" << std::endl;
	std::cout << "All 7 test passed. Success." << std::endl;
}