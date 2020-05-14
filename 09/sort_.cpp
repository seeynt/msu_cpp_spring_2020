#include "sort_.h"

static const size_t size_ = sizeof(uint64_t);

static void merge(size_t start, size_t end) {
    if (start == end)
        return;
    uint64_t a_val, b_val;
    size_t size_a, size_b, i = 0, j = 0;;

    auto a = std::to_string(start);
    auto b = std::to_string(end);
    auto c = "tmp" + a;

    std::ifstream fa(a, std::ios::binary);
    std::ifstream fb(b, std::ios::binary);
    std::ofstream fc(c, std::ios::binary);

    fa.read(reinterpret_cast<char *>(&size_a), sizeof(size_t));
    fb.read(reinterpret_cast<char *>(&size_b), sizeof(size_t));

    size_a += size_b;
    fc.write(reinterpret_cast<const char *>(&size_a), sizeof(size_t));
    size_a -= size_b;

    fa.read(reinterpret_cast<char *>(&a_val), size_);
    fb.read(reinterpret_cast<char *>(&b_val), size_);

    while (i < size_a && j < size_b) {
        if (a_val < b_val) {
            fc.write(reinterpret_cast<const char *>(&a_val), size_);
            fa.read(reinterpret_cast<char *>(&a_val), size_);
            ++i;
        }
        else {
            fc.write(reinterpret_cast<const char *>(&b_val), size_);
            fb.read(reinterpret_cast<char *>(&b_val), size_);
            ++j;
        }
    }

    if (i < size_a) {
        fc.write(reinterpret_cast<const char *>(&a_val), size_);
        while (fa.read(reinterpret_cast<char *>(&a_val), size_))
            fc.write(reinterpret_cast<const char *>(&a_val), size_);
    }
    if (j < size_b) {
        fc.write(reinterpret_cast<const char *>(&b_val), size_);
        while (fb.read(reinterpret_cast<char *>(&b_val), size_))
            fc.write(reinterpret_cast<const char *>(&b_val), size_);
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
    size_t one = 1;
    uint64_t val;

    std::ios_base::sync_with_stdio(false);
    std::ifstream fin(fname, std::ios::binary);
    std::ofstream fout;

    while (fin.read(reinterpret_cast<char *>(&val), sizeof(uint64_t))) {
        fout.open(std::to_string(n), std::ios::binary);
        fout.write(reinterpret_cast<const char *>(&one), sizeof(size_t));
        fout.write(reinterpret_cast<const char *>(&val), sizeof(uint64_t));
        fout.close();
        ++n;
    }

    auto first = pool.exec(merge_sort, 0, n / 2);
    auto second = pool.exec(merge_sort, n / 2, n);
    first.get();
    second.get();

    merge(0, n / 2);

    fin.close();
    fin.open(std::to_string(0).c_str(), std::ios::binary);
    fout.open(("sorted_" + fname).c_str(), std::ios::binary);

    fin.read(reinterpret_cast<char *>(&n), sizeof(size_t));

    while (fin.read(reinterpret_cast<char *>(&val), sizeof(uint64_t))) {
        fout.write(reinterpret_cast<const char *>(&val), sizeof(uint64_t));
    }

    remove(std::to_string(0).c_str());
}
