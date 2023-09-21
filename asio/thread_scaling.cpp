#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <memory>

using work = boost::asio::io_service::work;


class TPool {

public:



private:
    int num_of_thread_;
    boost::asio::io_service _io_service;
    std::unique_ptr<work> work_ptr;
    std::vector<std::thread> threads;
};



int main() {
    // Make io_service
    boost::asio::io_service _io_service;
    
    // Make io_service::work
    std::unique_ptr<work> work_ptr = std::make_unique<work>(_io_service);
    
    // Start and make threads available to the io_service
    constexpr int num_threads = 8;    
    std::array<std::thread, num_threads> threads;
    
    for (auto i = 0; i < num_threads; ++i)
    {
        threads[i] = std::thread([&_io_service]() {
            _io_service.run();
        });
    }
    
    // Make the threads work
    auto print_thread_id = []()
    {
        std::cout << "Current thread id: " << std::this_thread::get_id() << "n";
    };
    
    for (auto i = 0; i < num_threads * 2; ++i)
    {
        _io_service.post(print_thread_id);
    }
    
    // Reset work
    work_ptr.reset();
    
    // Wait for completion
    for (auto & thread : threads)
    {
        thread.join();
    }

}