#include <iostream>
#include <boost/asio.hpp>
#include <thread>

void Task1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Task1 executed by thread " << std::this_thread::get_id() << std::endl;
}

void Task2() {
    std::cout << "Task2 executed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    boost::asio::io_context io_context;

    std::thread thread1([&io_context]() {
        io_context.post(Task1);
        });

    std::thread thread2([&io_context]() {
        io_context.dispatch(Task2);
        });

    thread1.join();
    thread2.join();

    io_context.run();

    return 0;
}
