#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <memory>

void MyAsyncOperation(boost::asio::io_context& io_context, bool& condition_met) {
    // Simulate an asynchronous operation
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Mark the condition as met
    condition_met = true;

    // Notify the io_context to stop by posting an empty task
    io_context.post([]() {});
}

int main() {


    // Make io_service
    boost::asio::io_service _io_service;

    // Make io_service::work

    using work = boost::asio::io_service::work;
    std::unique_ptr<work> work_ptr = std::make_unique<work>(_io_service);

    // Self resetting work
    auto io_work = [](std::unique_ptr<work>& work_)
        {
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(6000ms);

            // After reset the worker, ioService will stop
            // Now reset is a method of unique_ptr that will stop the work.
            work_.reset();     
        };

    // Post work
    _io_service.post(std::bind(io_work, std::ref(work_ptr)));

    // Runs until work is reset, since no worker, become non-blocking.

    _io_service.run();

    // Now, the ioService will stop processing new tasks.
    // Other code, if needed.


    /*

    boost::asio::io_context io_context;

    bool condition_met = false;

    // Create a unique_ptr to manage the work object
    std::unique_ptr<boost::asio::io_context::work> work;

    // Launch an asynchronous operation
    std::thread([&io_context, &condition_met, &work]() {
        MyAsyncOperation(io_context, condition_met);

        // Once the operation is done, reset the work object
        work.reset();
        }).detach();

        // Run the io_context until the condition is met
        while (!condition_met) {
            io_context.run_one(); // Run a single handler
        }

        std::cout << "Condition met. Stopping io_context." << std::endl;

        // The io_context will stop when there is no more work
        io_context.run(); // This will exit the io_context's run loop

        std::cout << "io_context has exited." << std::endl;
*/
     
    return 0;
}
