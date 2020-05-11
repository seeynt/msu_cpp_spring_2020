#include "sort_.h"
#include <iostream>
#include <vector>
#include <random>

void read_vector(std::vector<uint64_t>& v, std::string fname) {
	std::ifstream fin(fname);
	uint64_t val;

	v.clear();
	while (fin >> val)
		v.push_back(val);
}

void generate_file(std::string fname, size_t n) {
	std::ofstream fout(fname);
	std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;

    for (size_t i = 0; i < n; ++i)
    	fout << dis(gen) << ' ';
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::vector<uint64_t> raw;
    std::vector<uint64_t> sorted;

    read_vector(raw, "test1");
    sort_("test1");
    read_vector(sorted, "sorted_test1");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 1 passed (one number)" << std::endl;

    read_vector(raw, "test2");
    sort_("test2");
    read_vector(sorted, "sorted_test2");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 2 passed (same numbers)" << std::endl;

    read_vector(raw, "test3");
    sort_("test3");
    read_vector(sorted, "sorted_test3");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 3 passed (sorted array)" << std::endl;

    read_vector(raw, "test4");
    sort_("test4");
    read_vector(sorted, "sorted_test4");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 4 passed (reverse array)" << std::endl;

    generate_file("test5", 1000);
    read_vector(raw, "test5");
    sort_("test5");
    read_vector(sorted, "sorted_test5");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 5 passed (random array)" << std::endl;

	generate_file("test6", 10000);
    read_vector(raw, "test6");
    sort_("test6");
    read_vector(sorted, "sorted_test6");
    std::sort(raw.begin(), raw.end());
    assert(raw == sorted);
    std::cout << "Test 6 passed (big random array)" << std::endl;

    std::cout << "All 6 tests passed. Success." << std::endl;
    return 0;
}
