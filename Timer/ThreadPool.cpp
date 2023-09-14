#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) {
    
    for (size_t i = 0; i < numThreads; ++i) {

        workers_.emplace_back([this]() {
            while (true) {
                std::pair<TimerListener*, int> listenerInfo;
                {
                    std::unique_lock<std::mutex> lock(queueMutex_);
                    condition_.wait(lock, [this]() { return !tasks_.empty() || stop_; });
                    if (stop_ && tasks_.empty()) return;
                    listenerInfo = std::move(tasks_.front());
                    tasks_.pop();
                }
                TimerListener* listener = listenerInfo.first;
                int event = listenerInfo.second;
                listener->timer(event);
            }
        });
    }
}

void ThreadPool::enqueue(TimerListener* listener, int event) {
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        tasks_.emplace(listener, event);
    }
    condition_.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        stop_ = true;
    }
    condition_.notify_all();
    for (std::thread &worker : workers_) worker.join();
}
