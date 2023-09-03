#include<iostream>
#include<thread>
#include<functional>

using namespace std;


void foo() {
	cout << "Simple thread function.\n";
}

void do_operation() {
	cout << "perform other operation.\n";
	throw runtime_error("This is RT exception.");
}


// Or, We can use RAII appoech to join the thread. 
// so that if thread going to distroy, it must be join into dtor. 

class ThreadWrapper {
	thread &m_thread;
public:
	// delete copy ctor & assignment operator overload.
	// --
	ThreadWrapper(std::thread &thread):m_thread(thread){}
	~ThreadWrapper() {
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}
};


int main() {

	
	thread th(foo);
	//do_operation();			// Exception thrown
	//th.join();				// Menas never join the thread.
		// In this case program abort, but why?
		// Ans: we either need to detach or join the child thread before parent terminate.
		// if not, when thread object (th) going to discruct then its distructor check for 
		// its joinable, if that time still it is joinable then it will abort the ecexution.  
	try {
		do_operation();
		th.join();
	}
	catch (exception & e) {
		cout << "catch expection\n";
		th.join();
	}


	
	// By using Warpper, RAII.
	std::thread th1(foo);            // one problem is, it imidiatly start execution once constructed.

	ThreadWrapper wrapper(th1);

	// now no need to join the th1, once goes out of scope 
	// wrapper distroctor join the thread. 

	return 0;
}
