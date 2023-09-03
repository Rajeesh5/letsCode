// std::lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::try_lock

using namespace std;
int amount = 0;
std::timed_mutex m;

void increment(int i) {
	if (m.try_lock_for(std::chrono::seconds(1))) {
		++amount;
		this_thread::sleep_for(chrono::seconds(2));
		std::cout << "Thread " << i << " Entered" << endl;
		m.unlock();
	}
	else {
		cout << "Thread " << i << " Could not Enter" << endl;
	}
}

//There are so many try_lock function
std::try_lock
std::mutex::try_lock
std::shared_lock::try_lock
std::timed_mutex::try_lock
std::unique_lock::try_lock
std::shared_mutex::try_lock
std::recursive_mutex::try_lock
std::shared_timed_mutex::try_lock
std::recursive_timed_mutex::try_lock




int main() {
	thread th2(increment, 2);
	thread th1(increment, 1);
	

	th1.join();
	th2.join();

	cout << "Amt :: " << amount << endl;
	return 0;
}


