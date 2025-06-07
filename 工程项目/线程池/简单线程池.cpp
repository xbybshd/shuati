/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {
public:
    ThreadPool(size_t numsThreads);
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

private:
    void worker();
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

ThreadPool::ThreadPool(size_t numThreads)
    : stop(false) {
    for (size_t i = 0; i < numThreads; i++) {
        threads.emplace_back([this] { this->worker(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& thread : threads) {
        thread.join();
    }
}

template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
    using return_type = std::invoke_result_t<F, Args...>;
    auto task = std::make_shared<std::packaged_task<return_type()>>([f = std::forward<F>(f), ... args = std::forward<Args>(args)]() mutable { return std::invoke(f, std::forward<Args>(args)...); });
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) {
            throw std::runtime_error("enqueue stopped");
        }
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
                return;
            }
            task = std::move(tasks.front());
            this->tasks.pop();
        }
        task();
    }
}

void simpleTask(int num, ofstream& fcout) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    fcout << "Task " << num << " executed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    {
        ThreadPool pool(4); // 创建一个包含4个线程的线程池

        // 添加多个任务到线程池
        for (int i = 0; i < 10; ++i) {
            pool.enqueue(simpleTask, i, std::ref(fcout));
        }

        // 等待一段时间，让任务有足够时间执行
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    fcin.close();
    fcout.close();

    return 0;
}