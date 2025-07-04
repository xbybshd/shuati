#include <atomic>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <thread>
#include <unistd.h>

// 互斥锁
class SimpleMutex {
private:
    std::atomic<int> lock_flag { 0 }; // 0: 未锁定, 1: 锁定
    int futex_addr; // 用于 futex 系统调用的地址

    // Linux futex 系统调用封装
    void futex_wait() {
        syscall(SYS_futex, &futex_addr, FUTEX_WAIT, 1, nullptr, nullptr, 0);
    }
    void futex_wake() {
        syscall(SYS_futex, &futex_addr, FUTEX_WAKE, 1, nullptr, nullptr, 0);
    }

public:
    void lock() {
        // 尝试原子交换：0 -> 1，若失败则说明锁被占用
        while (lock_flag.exchange(1, std::memory_order_acquire) == 1) {
            // 锁被占用时，通过 futex 挂起线程
            futex_wait();
        }
    }

    void unlock() {
        // 释放锁并唤醒等待线程
        lock_flag.store(0, std::memory_order_release);
        futex_wake();
    }
};

// 自旋锁
#include <atomic>
#include <thread>

class SpinLock {
private:
    std::atomic<bool> locked { false }; // false: 未锁定, true: 锁定

public:
    void lock() {
        bool expected = false;
        while (!locked.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
            expected = false; // 失败后恢复 expected 值
        }
    }

    void unlock() {
        locked.store(false, std::memory_order_release);
    }
};