#include <algorithm> // for std::copy, std::move
#include <cstddef> // for size_t, ptrdiff_t
#include <initializer_list>
#include <stdexcept> // for std::out_of_range
#include <utility> // for std::swap

template <typename T>
class Vector {
private:
    T* data_ = nullptr; // 存储元素的数组
    size_t size_ = 0; // 当前元素数量
    size_t capacity_ = 0; // 当前分配的内存容量

    // 辅助函数：增长容量
    void grow_capacity(size_t new_capacity) {
        if (new_capacity <= capacity_)
            return;

        // 通常按2倍增长，但至少为new_capacity
        size_t new_cap = std::max(capacity_ * 2, new_capacity);
        reserve(new_cap);
    }

public:
    // 类型别名（与STL兼容）
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    // 构造函数
    Vector() = default;

    explicit Vector(size_t count)
        : data_(new T[count])
        , size_(count)
        , capacity_(count) {}

    Vector(size_t count, const T& value)
        : Vector(count) {
        std::fill_n(data_, count, value);
    }

    Vector(std::initializer_list<T> init)
        : Vector(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    // 拷贝构造函数
    Vector(const Vector& other)
        : Vector(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // 移动构造函数
    Vector(Vector&& other) noexcept
        : data_(other.data_)
        , size_(other.size_)
        , capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    // 析构函数
    ~Vector() {
        delete[] data_;
    }

    // 拷贝赋值
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // 移动赋值
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    // 元素访问
    T& operator[](size_t pos) { return data_[pos]; }
    const T& operator[](size_t pos) const { return data_[pos]; }

    T& at(size_t pos) {
        if (pos >= size_)
            throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    const T& at(size_t pos) const {
        if (pos >= size_)
            throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }

    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    // 迭代器
    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cend() const noexcept { return data_ + size_; }

    // 容量
    bool empty() const noexcept { return size_ == 0; }
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_)
            return;

        T* new_data = new T[new_capacity];
        std::move(data_, data_ + size_, new_data);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void shrink_to_fit() {
        if (size_ == capacity_)
            return;

        Vector tmp(*this);
        swap(tmp);
    }

    // 修改器
    void clear() noexcept {
        size_ = 0;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow_capacity(size_ + 1);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            grow_capacity(size_ + 1);
        }
        data_[size_++] = std::move(value);
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            grow_capacity(size_ + 1);
        }
        new (&data_[size_++]) T(std::forward<Args>(args)...);
    }

    void pop_back() {
        --size_;
    }

    void resize(size_t count) {
        if (count > capacity_) {
            reserve(count);
        }
        size_ = count;
    }

    void resize(size_t count, const T& value) {
        size_t old_size = size_;
        resize(count);
        if (count > old_size) {
            std::fill(data_ + old_size, data_ + count, value);
        }
    }

    void swap(Vector& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }
};

// 非成员函数
template <typename T>
void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}