#include "sort_.h"

static void merge(size_t start, size_t end) {
    if (start == end)
        return;
    uint64_t a_val, b_val;

    auto a = std::to_string(start);
    auto b = std::to_string(end);
    auto c = "tmp" + a;

    std::ifstream fa(a);
    std::ifstream fb(b);
    std::ofstream fc(c);

    fa >> a_val;
    fb >> b_val;

    while (!fa.eof() && !fb.eof()) {
        if (a_val < b_val) 
            fc << a_val << ' ', fa >> a_val;
        else
            fc << b_val << ' ', fb >> b_val;
    }

    if (!fa.eof()) {
        fc << a_val << ' ';
        while (fa >> a_val)
            fc << a_val << ' ';
    }
    if (!fb.eof()) {
        fc << b_val << ' ';
        while (fb >> b_val)
            fc << b_val << ' ';
    }

    remove(a.c_str());
    remove(b.c_str());
    rename(c.c_str(), a.c_str());
}

static void merge_sort(size_t start, size_t end) {
    size_t n = end - start;
    for (size_t st = 1; st < n; st *= 2)
        for (size_t i = 0; i + st < n; i += 2 * st)
            merge(start + i, start + i + st);
}

void sort_(const std::string& fname) {
    ThreadPool pool(2);
    size_t n = 0;
    uint64_t val;

    std::ios_base::sync_with_stdio(false);
    std::ifstream fin(fname);
    std::ofstream fout;

    while (fin >> val) {
        fout.open(std::to_string(n));
        fout << val << ' ';
        fout.close();
        ++n;
    }

    auto first = pool.exec(merge_sort, 0, n / 2);
    auto second = pool.exec(merge_sort, n / 2, n);
    first.get();
    second.get();

    merge(0, n / 2);
    rename(std::to_string(0).c_str(), ("sorted_" + fname).c_str());
}