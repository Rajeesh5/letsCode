#include<iostream>
#include<thread>
#include<mutex>
#include<algorithm>
#include<functional>


using namespace std;


// Unary_function taktes at least one parameter.
class Sample : public unary_function<int,void> {
public: 
	void operator() (int x=0) const{
		for (int i = 0; i < 100; i++) {
			cout << "From Sample::" << i << endl;
		}
	}
};


void sample_fun() {
	for (int i = 0; i < 100; i++) {
		cout << "From Sample::" << i << endl;
	}
}

int main() {
	//thread th((Sample()));
	thread th(sample_fun);
	for (int i = 0; i < 100; i++) {
		cout << "From Main::"<< i << endl;
	}
	th.join();
	return 0;
}