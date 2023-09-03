#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>

using namespace std;

std::condition_variable cv;
std::mutex mu;
int counter = 1;

void print_first() {
	unique_lock<mutex> locker(mu);
	cout << "Alwease print First. " << std::this_thread::get_id() << endl;
	counter++;
	// 1. cv.notify_one();
	// <non-cretical section>
	// 2. this_thread::sleep_for(chrono::minutes(1));	
	// <end>
	// 3. locker.unlock();   // or this should automatically released here.
}

// Notes:: think about the commented lines (1,2,3):
// if we commented ponit::1 then,
// never notify to the second thread for wake-up.
// point::2 is non-critical section, we must release the mutex after notify.
// otherwise thread1 sleeps for a min, without releasing the mutex, and thread2
// keep waiting for unlock the mutex (point::3) 




void print_second() {
	unique_lock<mutex> locker(mu);
	cv.wait(locker, [] {return !(counter == 1); });
	cout << "This is second. " << std::this_thread::get_id() << endl;
}


int main() {

	std::thread th2(print_second);
	std::thread th1(print_first);

	th1.join();
	th2.join();
}