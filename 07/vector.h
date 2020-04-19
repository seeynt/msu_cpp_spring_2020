#include "allocator.h"
#include "iterator.h"
#include <iterator>
#include <exception>

template<class T, class Alloc = std::allocator<T>>

class Vector {
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using const_reference = const T&;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;

    pointer array_;
    size_type capacity_;
    size_type current_;
    Alloc allocator;

public:
    explicit Vector(size_type sz = 0) {
        array_ = allocator.allocate(sz);
        capacity_ = sz;
        current_ = sz;
    }

    Vector(size_type sz, const_reference& defaultValue) {
        array_ = allocator.allocate(sz);
        capacity_ = sz;
        current_ = sz;

        for (size_type i = 0; i < current_; ++i)
            array_[i] = defaultValue;
    }

    Vector(std::initializer_list<value_type> init) {
        array_ = allocator.allocate(init.size());
        capacity_ = current_ = init.size();
        auto i = init.begin();
        for (size_type j = 0; i < init.end(); ++i, ++j)
            array_[j] = *i;
    }

    Vector(Vector&& other) noexcept {
        array_ = other.array_;
        current_ = other.current_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
    }

    Vector(const Vector& other) {
        array_ = allocator.allocate(other.current_);
        capacity_ = current_ = other.current_;
        for (size_type i = 0; i < current_; ++i)
            array_[i] = other.array_[i];
    }

    Vector operator=(const Vector& other) {
        if (capacity_ < other.current_)
            this->reserve(other.current_);
        current_ = other.current_;
        for (size_type i = 0; i < current_; ++i)
            array_[i] = other.array_[i];
        return *this;
    }

    Vector operator=(Vector&& other) {
        allocator.deallocate(array_, capacity_);
        array_ = other.array_;
        current_ = other.current_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        return *this;
    }

    ~Vector() {
        allocator.deallocate(array_, capacity_);
    }

    iterator begin() noexcept { return iterator(array_); }
    iterator end() noexcept { return iterator(array_ + current_); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    reference operator[](size_type ind) {
        if (ind >= current_)
            throw std::out_of_range("Index is out of range");
        return array_[ind];
    }

    const_reference operator [](size_type ind) const {
        if (ind >= current_)
            throw std::out_of_range("Index is out of range");
        return array_[ind];
    }

    void push_back(T&& value) {
        if (current_ == capacity_)
            this->reserve(capacity_ * 2);
        array_[current_++] = value;
    }

    void push_back(const T& value) {
        if (current_ == capacity_)
            this->reserve(capacity_ * 2);
        array_[current_++] = value;
    }

    void pop_back() {
        --current_;
    }

    void resize(size_type sz) {
        if (sz > current_)
            this->reserve(sz);
        current_ = sz;
    }

    void resize(size_type sz, const_reference defaultValue) {
        if (sz > current_)
            this->reserve(sz);
        for (size_type i = current_; i < sz; ++i)
            array_[i] = defaultValue;
        current_ = sz;
    }

    size_type size() const noexcept {
        return current_;
    }

    void reserve(size_type sz) {
        if (sz <= capacity_)
            return;
        pointer new_array = allocator.allocate(sz);
        for (size_type i = 0; i < current_; ++i)
            new_array[i] = array_[i];
        allocator.deallocate(array_, capacity_);
        array_ = new_array;
        capacity_ = sz;

    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    void clear() noexcept {
        current_ = 0;
    }

    bool empty() noexcept {
        return !current_;
    }
};
