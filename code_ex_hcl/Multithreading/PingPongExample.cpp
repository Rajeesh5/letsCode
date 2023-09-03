#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>

using namespace std;

std::condition_variable cv;
std::mutex mu;
int counter = 50;

void ping() {
	while (counter) {
		unique_lock<mutex> locker(mu);
		cout << counter-- << " ::ping" << endl;		
		
		// notify first before wait() but why ??
		cv.notify_one();		// I am done now, notify to the others (pong).
		cv.wait(locker);		// Unlock the mutex and put thread into waiting .
							

		// why wait donot has predicate function ?
		// 1. ping, pong is mutually-exclusive, that means if pong is true then ping is 
		//    always false.
		// 2. since both ping & pong are small function, it has less likely condition of
		//    suprious wake.
	}
}

void pong() {
	while (counter) {
		unique_lock<mutex> locker(mu, std::defer_lock);   // Defer lock..
		locker.lock();

		// Predicate in wait ensure, ping excecuted first. 
		cv.wait(locker, [] { return !(counter % 2 == 0); });
		cout << counter-- << " ::Pong" << endl;

		locker.unlock();
		cv.notify_one();
	}
}

// If Pong get executed first::
//	1. predicate on cv is false, release the mutex and went to sleep.
//  2. Ping() completed its task, cv.wait put thread on hold, release the mutex
//     and notify the other (pong) which was sleeping mode.
//  3. now Pong() get acitivated aquire the lock, after his work unlock the
//     thread and notify to Ping.


int main() {

	std::thread th2(pong);
	std::thread th1(ping);

	th1.join();
	th2.join();
	return 0;
}