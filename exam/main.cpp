#include "sum.h"
#include <iostream>

int generate_file(int n) {
	std::ofstream fout("test.txt");
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= n; ++j)
			fout << j << ' ';
		fout << '\n';
	}
	return n * n * (n + 1) / 2;
}

int main() {
	int result;
	result = generate_file(1);
	assert(result == sum_file("test.txt"));

	result = generate_file(0);
	assert(result == sum_file("test.txt"));

	result = generate_file(5);
	assert(result == sum_file("test.txt"));

	result = generate_file(50);
	assert(result == sum_file("test.txt"));

	result = generate_file(234);
	assert(result == sum_file("test.txt"));

	result = generate_file(1000);
	assert(result == sum_file("test.txt"));

	remove("test.txt");
	std::cout << "All tests passed. Success" << std::endl;
	return 0;
}