#include <iostream>
#include <boost/asio.hpp>
#include <functional>
#include <thread>

class Task {
public:
    Task(int id, std::function<void()> callback) : id_(id), callback_(callback) {}

    void execute() {
        if (callback_) {
            callback_();
        }
    }

private:
    int id_;
    std::function<void()> callback_;
};

class EventHandler {
public:
    EventHandler(boost::asio::io_service& io_service, int numThreads)
        : io_service_(io_service), work_(io_service) {
        for (int i = 0; i < numThreads; ++i) {
            threads_.emplace_back([this]() {
                io_service_.run();
            });
        }
    }

    void addTask(Task task) {
        io_service_.post([&]() {
            task.execute();
        });
    }

    ~EventHandler() {
        io_service_.stop();
        for (auto& thread : threads_) {
            thread.join();
        }
    }

private:
    boost::asio::io_service& io_service_;
    boost::asio::io_service::work work_; // Ensures the io_service doesn't exit prematurely
    std::vector<std::thread> threads_;
};

int main() {
    boost::asio::io_service io_service;
    const int numThreads = 3; // Number of threads in the vector
    EventHandler eventHandler(io_service, numThreads);

    // Create and add tasks with IDs and associated callbacks
    Task task1(1, []() { std::cout << "Task 1 executed" << std::endl; });
    Task task2(2, []() { std::cout << "Task 2 executed" << std::endl; });
    Task task3(3, []() { std::cout << "Task 3 executed" << std::endl; });







    // Add tasks to the handler, and they will be executed by available threads
    eventHandler.addTask(task1);
    eventHandler.addTask(task2);
    eventHandler.addTask(task3);

    // The tasks will be executed as soon as they are added

    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
