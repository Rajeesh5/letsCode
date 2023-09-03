#include<iostream>
#include<thread>
#include<functional>

//using namespace std;


class ThreadWrapper {

	std::thread m_thread;

public:
	//copy & assigment ctor.
	ThreadWrapper(const ThreadWrapper&) = delete;
	ThreadWrapper& operator = (const ThreadWrapper&) = delete;    // v1=v2 or, v1.opeartor=(v2)

	// move copy & assigment ctor.
	// Note: move ctor and assigment op doesnot take const paramanter.
	// becoase it need to convert paramenter r-values to l-values and 
	// we know hat l-valves are modificable.

	ThreadWrapper(ThreadWrapper&&) noexcept;
	ThreadWrapper& operator =(ThreadWrapper&&) noexcept;
	ThreadWrapper(std::function<void()>);

	~ThreadWrapper();
};

ThreadWrapper::ThreadWrapper(std::function<void()> callback_fn) : m_thread(callback_fn) {}

ThreadWrapper& ThreadWrapper::operator= (ThreadWrapper&& wraper) noexcept{
	std::cout << "Move assigment called \n";
	if (m_thread.joinable()) {
		m_thread.join();
	}
	m_thread = std::move(wraper.m_thread);
	return *this;
}

ThreadWrapper::ThreadWrapper(ThreadWrapper&& wraper) noexcept
	:m_thread(std::move(wraper.m_thread)) {
	std::cout << "Move ctor called\n";
}

ThreadWrapper::~ThreadWrapper() {
	if (m_thread.joinable()) {
		std::cout << "joined thread id::" << std::this_thread::get_id() << std::endl;
		m_thread.join();
	}
}

void simple_function() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "From simple_function thread id::" << std::this_thread::get_id() << std::endl;
}

class FunctorClass {
public:
	void operator () ()	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "From functor_class thread id::" << std::this_thread::get_id() << std::endl;
	}
};


int main() {
	// Intialize warpper with function.
	ThreadWrapper th1(simple_function);
	
	// Intialize wraper with functor method.
	ThreadWrapper th2([]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "From functor_mthod thread id::" << std::this_thread::get_id() << std::endl;
		});

	// Intialize wraper with functor class.
	ThreadWrapper th3((FunctorClass()));

	std::cout << "From main thread id::" << std::this_thread::get_id() << std::endl;
	return 0;
}