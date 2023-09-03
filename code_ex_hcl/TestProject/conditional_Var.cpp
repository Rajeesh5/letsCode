#include <iostream>
#include <string>
#include <thread>
#include <mutex>
//#include <condition_variable>

std::mutex m;
std::condition_variable cv12;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);

    cv12.wait(lk, [] {return ready; });    // Sleep the release the mutex, becasue ready is false. 

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;

    // swith back to the main thread... but still holding the mutex...
    std::this_thread::sleep_for(std::chrono::seconds(10));      
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv12.notify_one();
}

int main()
{
    std::thread worker(worker_thread);
    std::this_thread::sleep_for(std::chrono::seconds(1));     // Make sure worker should activate first 

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard <std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }   // Release the lock then notify the worker.
    cv12.notify_one();     

    // Note:: Even after notify, it doesnot mean a guarenty to excute worker thread immdeatly.
    //        small time of sleep for main insure for guarentied context switch.    
   
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    
    // wait for the worker
    {
        //main thread will wait till worker doesnot release the mutex in next 10 second
        std::unique_lock <std::mutex >lk(m);
        std::cout << "now main acquire the mextex\n";
        cv12.wait(lk, [] {return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
    return 0;
}