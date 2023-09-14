#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>

#include "TimerListener.h"

class ThreadPool {

public:
    ThreadPool(size_t numThreads);
    void enqueue(TimerListener* listener, int event);
    ~ThreadPool(); 

private:
    std::vector<std::thread> workers_;
    std::queue<std::pair<TimerListener*, int>> tasks_;

    std::mutex queueMutex_;
    std::condition_variable condition_;
    bool stop_ = false;
};