#include <iostream>
#include <boost/asio.hpp>
#include <functional>
#include <thread>
#include <mutex>


std::mutex m;

using namespace std;
    
// Create and add tasks with IDs and associated callbacks
auto task1 = [](thread::id &id) { m.lock(); std::cout << "Task 1 executed by" << id << std::endl; m.unlock();};
auto task2 = [](thread::id &id) { m.lock(); std::cout << "Task 2 executed by" << id << std::endl; m.unlock(); };
auto task3 = [](thread::id &id) { m.lock(); std::cout << "Task 3 executed by" << id << std::endl; m.unlock(); };

void resetWork(unique_ptr<boost::asio::io_service::work > &work_){
    this_thread::sleep_for(chrono::seconds(1));
    work_.reset();
}

int main() {
    boost::asio::io_service io_service_;
    boost::asio::io_service::work work_(io_service_);

    //auto work_ptr = make_unique<boost::asio::io_service::work >(io_service_);

    thread th1 = thread([&] { 
        io_service_.post( std::bind(task1 , this_thread::get_id() ));
        io_service_.run(); 
    } );
    
    thread th2 = thread([&] { 
        io_service_.post( std::bind(task2 , this_thread::get_id() )); 
        io_service_.run();
    } );

    thread th3 = thread([&] { 
        io_service_.post( std::bind(task3 , this_thread::get_id() )); 
        io_service_.run();
    } );

    // io_service_.post( std::bind(resetWork, std::ref(work_ptr)));
    // io_service_.run();       // I am not sure about this line

    // this_thread::sleep_for(chrono::seconds(1));
    // io_service_.stop();
    

    // Problems::
    // Thread are not joinable until call stop()
    // before stop need to nap so that threads completed its execution.
    // But this is not correct. 
    // program should be automatically stoped when exexcution over.

    th1.join();
    th2.join();
    th3.join();


    std::cout << "End" << std::endl;

    return 0;
}
