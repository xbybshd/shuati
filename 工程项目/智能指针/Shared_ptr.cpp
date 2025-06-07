#include <atomic>
#include <utility> // std::swap

template <typename T>
class SharedPtr {
private:
    T* ptr;
    std::atomic<size_t>* ref_count;

    // 增加引用计数
    void AddRef() {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    // 减少引用计数，并在计数为0时释放资源
    void Release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

public:
    // 默认构造函数
    SharedPtr()
        : ptr(nullptr)
        , ref_count(nullptr) {}

    // 构造函数（接管裸指针）
    explicit SharedPtr(T* p)
        : ptr(p)
        , ref_count(new std::atomic<size_t>(1)) {}

    // 拷贝构造函数（线程安全）
    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr)
        , ref_count(other.ref_count) {
        AddRef();
    }

    // 移动构造函数
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr)
        , ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // 析构函数（线程安全）
    ~SharedPtr() {
        Release();
    }

    // 拷贝赋值（线程安全）
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            Release(); // 释放当前资源
            ptr = other.ptr;
            ref_count = other.ref_count;
            AddRef(); // 增加新资源的引用
        }
        return *this;
    }

    // 移动赋值
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            Release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // 解引用
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 获取引用计数
    size_t UseCount() const { return ref_count ? *ref_count : 0; }

    // 交换两个 SharedPtr
    void Swap(SharedPtr& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }
};