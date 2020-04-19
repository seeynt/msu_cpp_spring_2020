#include <limits>

template<class T>

class Allocator {
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;

public:
    reference allocate(size_type sz) {
        return new T[sz];
    }

    void deallocate(pointer p, size_type n = 0) {
        (void)n;
        delete[] p;
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<value_type>::max();
    }
};
