#include<iostream>
#include<thread>
#include<future>
#include<mutex>
using namespace std;
/* async() are used in the same ways as thread(), bind() */


std::mutex mu1;
std::condition_variable cv1;
bool isChanged1 = false;
int counter = 5;


void print() {
	unique_lock<mutex> lock(mu1);
	cout << "Print First\n";
	isChanged1 = true;
	cv1.notify_one();			// If you dont notify, the main thread 
								// alwayes keep waiting. never print "Always Last"
}


void ping() {
	while (counter>=0) {
		unique_lock<mutex> locker(mu1);
		cv1.wait(locker, []() {return !(counter % 2); });
		if (counter >= 0) {
			cout << counter-- << " ::ping" << endl;
		}
		cv1.notify_one();				
	}
}

void pong() {
	while (counter>=0) {
		unique_lock<mutex> locker(mu1);		

		// Predicate in wait ensure, ping excecuted first. 
		cv1.wait(locker, [] { return (counter % 2); });
		if (counter >= 0) {
			cout << counter-- << " ::Pong" << endl;
		}
		cv1.notify_one();
	}
}

int counter1 = 1;
void print_first() {
	unique_lock<mutex> locker(mu1);
	cout << "Alwease print First. " << std::this_thread::get_id() << endl;
	counter1++;
	cv1.notify_one(); 
}

// Never notify the others before unlock the mutex.
// if thread still holding the mutex, notified thread keep waiting for unlock the mutex.  



void print_second() {
	unique_lock<mutex> locker(mu1);
	cv1.wait(locker, [] {return !(counter1 == 1); });
	cout << "This is second. " << std::this_thread::get_id() << endl;
}



int main() {
	/*
	thread t(print);
	unique_lock<mutex> lock(mu1);
	cv1.wait(lock, []() {return isChanged1; });
	cout << "Always Last\n";
	t.join();
	*/

	thread t1(print_second);
	thread t2(print_first);

	t1.join();
	t2.join();

	return 0;

}
