template <class T>

class Iterator {
    T* ptr_;
public:
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    Iterator<value_type> operator=(const Iterator<value_type>& other) { ptr_ = other.ptr_; }

    bool operator==(const Iterator<value_type>& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<value_type>& other) const {
        return !(*this == other);
    }

    bool operator<(const Iterator<value_type>& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const Iterator<value_type>& other) const {
        return !(*this < other) && (*this != other);
    }

    bool operator<=(const Iterator<value_type>& other) const {
        return !(*this > other);
    }

    bool operator>=(const Iterator<value_type>& other) const {
        return !(*this < other);
    }

    Iterator operator++() {
        ++ptr_;
        return *this;
    }

    Iterator operator--() {
        --ptr_;
        return *this;
    }

    Iterator operator+(size_type n) const {
        return Iterator<value_type>(ptr_ + n);
    }

    Iterator operator-(size_type n) const {
        return Iterator<value_type>(ptr_ - n);
    }

    difference_type operator-(const Iterator& other) const {
        return ptr_ - other.ptr_;
    }

    pointer operator->() const {
        return &**ptr_;
    }

    reference operator*() const {
        return *ptr_;
    }
};
