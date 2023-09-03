#include<iostream>
#include<thread>
#include<mutex>
#include <future>

int factorial(std::future<int> &f) {

	int n = f.get();   //sleep until get the value.
	int res = 1;
	for(int i = 2; i < n; i++) {
		res *= i;
	}
	return res;

}

int main() {

	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));  //Launching child thread
	std::this_thread::sleep_for(std::chrono::seconds(1));                     
	p.set_value(9);		     //It will causes to wakeup child thread (fectorial) again.
	std::cout << fu.get();   //Get the value back from child thread.
	return 0;
}