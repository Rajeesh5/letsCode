#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t num_threads) : io_context_(), work_guard_(boost::asio::make_work_guard(io_context_)) {
        for (size_t i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this]() {
                io_context_.run();
                });
        }
    }

    ~ThreadPool() {
        io_context_.stop();
        for (auto& thread : threads_) {
            thread.join();
        }
    }

    template <typename Task>
    void post(Task&& task) {
        io_context_.post(std::forward<Task>(task));
    }

private:
    boost::asio::io_context io_context_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard_;
    std::vector<std::thread> threads_;
};

void MyTask(int task_number) {
    std::cout << "Task " << task_number << " executed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    const int num_threads = 4;
    ThreadPool thread_pool(num_threads);

    for (int i = 0; i < 10; ++i) {
        thread_pool.post([i]() {
            MyTask(i);
            });
    }

    // Sleep for a while to allow tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
