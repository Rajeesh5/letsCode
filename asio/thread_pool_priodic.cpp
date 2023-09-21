#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t num_threads) : io_context_(), threads_(num_threads), work_counter_(0) {
        for (size_t i = 0; i < num_threads; ++i) {
            threads_[i] = std::thread([this]() {
                io_context_.run();
                });
        }
    }

    ~ThreadPool() {
        // Stop the io_context once all work is done
        while (work_counter_.load() > 0) {
            io_context_.stop();
            std::this_thread::yield();
        }

        for (auto& thread : threads_) {
            thread.join();
        }
    }

    template <typename Task>
    void post(Task&& task) {
        // Increment the work counter before posting the task
        work_counter_.fetch_add(1);
        io_context_.post([this, task]() {
            task();
            work_counter_.fetch_sub(1);
            });
    }

    void runPeriodicTask(const std::function<void()>& task, const std::chrono::milliseconds& interval) {
        auto timer = std::make_shared<boost::asio::deadline_timer>(io_context_, interval);

        std::function<void(const boost::system::error_code&)> handler = [this, task, timer](const boost::system::error_code& ec) {
            if (!ec) {
                task();
                timer->expires_at(timer->expires_at() + interval);
                timer->async_wait(handler);
            }
            };

        timer->async_wait(handler);
    }

private:
    boost::asio::io_context io_context_;
    std::vector<std::thread> threads_;
    std::atomic<int> work_counter_;
};

void MyTask(int task_number) {
    std::cout << "Task " << task_number << " executed by thread " << std::this_thread::get_id() << std::endl;
}

void PeriodicTask() {
    std::cout << "Periodic task executed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    const int num_threads = 4;
    ThreadPool thread_pool(num_threads);

    for (int i = 0; i < 10; ++i) {
        thread_pool.post([i]() {
            MyTask(i);
            });
    }

    // Run a periodic task every 1 second
    thread_pool.runPeriodicTask(PeriodicTask, std::chrono::seconds(1));

    // Sleep for a while to allow tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
