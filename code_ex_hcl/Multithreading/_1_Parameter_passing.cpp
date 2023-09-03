#include<iostream>
#include<thread>
#include<mutex>



class Sample {
public:
	void sample_method(const int& x) {
		int& y = const_cast<int&>(x);
		std::cout << "From sample:: "<< y << std::endl;		
		y++;
	}

};

int main__1mh() {
	int x = 10;
	Sample sample;
	// std::thread th1(&Sample::sample_method, &sample, x);
	std::thread th1(&Sample::sample_method, &sample, std::ref(x));

	// since x is shared among two thread, so execution must be sync
	std::this_thread::sleep_for(std::chrono::seconds(1));
	th1.join();
	return 0;
}