#include<iostream>
#include<thread>
#include<future>
#include<mutex>
using namespace std;
/* async() are used in the same ways as thread(), bind() */


std::mutex mu;
bool isChanged = 0;
std::condition_variable cv;


class TestClass {
public:
	string note;
	void f(int x, char c) {
		note = "changed by f()";
		cout << "child thread ID by f():: " << this_thread::get_id() << endl;
		isChanged = 1;
		cv.notify_one();
	}
	long g(double x) {
		note = "changed by g()";
		cout << "child thread ID by g():: " << this_thread::get_id() << endl;
		return 0;
	}
	int operator()(int N) {
		note = "changed by oerator()";
		cout << "child thread ID by op():: " << this_thread::get_id() << endl;
		isChanged = 1;
		cv.notify_one();
		return 0;
	}
	void printNote() {
		cout << note.c_str() << endl;
		isChanged = 0;
		note = "Original";
		cv.notify_one();
	}
};


int main() {
	TestClass testObj;
	testObj.note = "Original";
	unique_lock<mutex> lock(mu, std::defer_lock );


	// How to launch different ways of thread ?
	// 1. Launching thread by callable object testObj(). Note testObj is passed 
	// by value so, any change by clild thread is not reflect in main.

	//std::thread t1(testObj, 6);	 //create copy_of_testObject and call operator().
								     //Original;
	//lock.lock();
	//cv.wait(lock, []() { return isChanged; });
	//testObj.printNote();
	//lock.unlock();
	//t1.join();

	
	// we can pass object via reference like:

	//std::thread t2(std::ref(testObj), 6);	// launch thread on testObj itself
	//										
	//lock.lock();
	//cv.wait(lock, []() { return isChanged; });
	//testObj.printNote();					// changed by oerator()
	//lock.unlock();
	//t2.join();


	// we can move object to child
	// thread but no longer accessible to main thread like:
	
	//std::thread t3(std::move(testObj), 6);
	//lock.lock();
	//cv.wait(lock, []() { return isChanged; });	
	//testObj.printNote();					// tsetObj is no longer valid for main thread.	
	//lock.unlock();
	//t3.join();


	
	//2. By using async method. Like first approach it also takes callable 
	// objectand varg as argument.

	//std::async(std::launch::async, testObj, 6);
	//lock.lock();
	//cv.wait(lock, []() { return isChanged; });	
	//testObj.printNote();			//Original since testObj passed by value.
	//lock.unlock();

	
	//3. Launching a thread using lembda function
	//std::thread t4([](int x) {cout << x * x; }, 6);
	//t4.join();

	

	//4. launching thread on class member function
	//std::thread t5(&TestClass::f, testObj, 56, 'z');
	//lock.lock();
	//cv.wait(lock, []() { return isChanged; });	
	//testObj.printNote();					// original
	//lock.unlock();
	//t5.join();


	
	//5. launching thread on class member function by ref
	std::thread t6(&TestClass::f, &testObj, 56, 'z');		// testObj.f(56, 'z')
															
	lock.lock();
	cv.wait(lock, []() { return isChanged; });
	testObj.printNote();									// change by f()
	lock.unlock();
	t6.join();
	
	/*
	std::thread t7(&TestClass::f, std::ref(testObj), 56, 'z');

	testObj.printNote();									// change by f()
	t6.join();
	t6.join();


	//6. By using temp variable and move into thread.
	std::thread(TestClass(), 6);


	std::future<int> fu3 = std::async(TestClass(), 4);
	// TestClass tmp;  tmp is moved to async(); 
																	 // create a task/thread with tmp(4);
	std::future<int> fu4 = std::async(testObj, 7);
	std::future<int> fu41 = std::async(std::ref(testObj), 7);
	// testObj(7);  Must use reference wrapper
	
	//std::future<int> fu5 = std::async(&testObj, 7);			// Won't compile
	
	std::future<void> fu1 = std::async(&TestClass::f, testObj, 56, 'z');
	// A copy of testObj invokes f(56, 'z')
	std::future<long> fu2 = std::async(&TestClass::g, &testObj, 5.6);
	// testObj.g(5.6); testObj is passed by reference

		// note: the parameter of the invocable are always passed by value, but the 
	// invokeable itself can be passed by ref.

	*/
	
	return 0;
}
