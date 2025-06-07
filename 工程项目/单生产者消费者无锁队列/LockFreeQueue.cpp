#include <atomic>
#include <iostream>
#include <vector>


template <typename T>
class LockFreeSPSCQueue {
public:
    explicit LockFreeSPSCQueue(size_t capacity)
        : buffer_(capacity)
        , capacity_(capacity)
        , head_(0)
        , tail_(0) {}

    bool push(const T& item) {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = (tail + 1) % capacity_;

        // 检查队列是否已满
        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false; // 队列满，插入失败
        }

        buffer_[tail] = item;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t head = head_.load(std::memory_order_relaxed);

        // 检查队列是否为空
        if (head == tail_.load(std::memory_order_acquire)) {
            return false; // 队列空，取出失败
        }

        item = buffer_[head];
        head_.store((head + 1) % capacity_, std::memory_order_release);
        return true;
    }

    bool empty() const {
        return head_.load(std::memory_order_acquire) ==
            tail_.load(std::memory_order_acquire);
    }

private:
    std::vector<T> buffer_;
    const size_t capacity_;
    std::atomic<size_t> head_; // 消费者读取位置
    std::atomic<size_t> tail_; // 生产者写入位置
};