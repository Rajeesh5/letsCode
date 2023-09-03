
#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

int counter = 0;
std::mutex mu;
std::condition_variable cv1;


void print_even() {

	while (counter <= 50) {
		{
			unique_lock<mutex> lock(mu);
			cv1.wait(lock, []() { return counter % 2 == 0; });
			cout << "Print Even::" << counter++ << endl;
		}    // Why nested block??
		     // before notify_one, need to free the lock, RAII approch.
		cv1.notify_one();
	}
}

void print_odd() {	
	while (counter < 50) {
		unique_lock<mutex> lock(mu);
		cv1.wait(lock, []() { return counter % 2 == 1; });
		cout << "Print Odd::" << counter++ << endl;			
		lock.unlock();    // unlocking manually.
		cv1.notify_one();
	}
}


int main() {

	thread t1(print_even);
	thread t2(print_odd);

	t1.join();
	t2.join();
	return 0;
}