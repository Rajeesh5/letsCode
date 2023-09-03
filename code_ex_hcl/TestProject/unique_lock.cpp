#include <iostream>
#include <string>
#include <thread>
#include <mutex>
//#include <condition_variable>

std::mutex mu;
std::condition_variable cv;

void worker_thread_ex()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(mu);

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // No mutex release...
}

int main()
{
    std::thread worker(worker_thread_ex);
    std::this_thread::sleep_for(std::chrono::seconds(1));     // Make sure worker should activate first 

    std::unique_lock<std::mutex> lk(mu);
    std::cout << "This line never prints.\n";
    worker.join();
    return 0;
}