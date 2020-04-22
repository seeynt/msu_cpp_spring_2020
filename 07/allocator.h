#include <limits>

template<class T>

class Allocator {
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;

public:
    pointer allocate(size_type sz) {
        auto ptr = (pointer)malloc(sz * sizeof(value_type));
        if (!ptr)
            throw std::bad_alloc();
        return ptr;
    }

    void deallocate(pointer ptr, size_type n = 0) {
        (void)n;
        free(ptr);
    }

    void construct(pointer ptr) {
        new(ptr) value_type();
    }

    void construct(pointer ptr, const_reference val) {
        new(ptr) value_type(val);
    }

    void destroy(pointer ptr) {
        ptr->~value_type();
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<value_type>::max();
    }
};
