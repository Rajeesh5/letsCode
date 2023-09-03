#include<iostream>
#include<thread>
#include<functional>


void first() {
	std::cout << "Inside thread first:" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void second() {
	std::cout << "Inside thread second:" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
}


int main() {
	std::cout << "Welcome To My Domain Starting the first thread.\n";
	std::thread example(first);
	std::cout << "Welcome To My Domain Starting the second thread...\n";
	std::thread example1(second);
	std::cout << "Thanks users we will waiting for the threads completion..." << std::endl;
	
	example.join();
	example1.join();
	
	std::cout << "Thread completion is over !\n";
}