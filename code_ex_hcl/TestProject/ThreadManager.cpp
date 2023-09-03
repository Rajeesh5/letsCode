#include<iostream>
#include<thread>
#include<functional>

using namespace std;



class ThreadWrapper {
	thread *m_thread;			// How do manage multiple thread in warpper class ?
								// i,e std::vector<std::thread> m_threadPool;
	bool isReady;
public:
	// donot excute the thread as soon as Warpper created.
	ThreadWrapper():isReady(true),m_thread(nullptr) {}
	
	// Need to start explicitly, once everything is intialized.. and ready to start.
	void startThread() {
		if (isReady) {
			m_thread= new std::thread(&ThreadWrapper::doJob, this);
		}
	}
	void doJob() {
		while (isReady) {      
			cout << "Thread Enabled\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	~ThreadWrapper() {
		isReady = false;             // Going to die, menas isReady=false; 
		if (m_thread->joinable()) {
			m_thread->join();
		}
		delete m_thread;
	}
};



class ThreadWrapperEx {
	thread &m_thread;			// How do manage multiple thread in warpper class ?
								// i,e std::vector<std::thread> m_threadPool;
	bool isReady;
public:
	// donot excute the thread as soon as Warpper created.
	ThreadWrapperEx( std::thread& th) : m_thread(th), isReady(true)  {}

	// Need to start explicitly, once everything is intialized.. and ready to start.
	void startThread() {
		if (isReady) {
			m_thread(&ThreadWrapper::doJob);   // how do I assign callback later.
		}
	}
	void doJob() {
		while (isReady) {
			cout << "Thread Enabled\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	~ThreadWrapperEx() {
		isReady = false;             // Going to die, menas isReady=false; 
		if (m_thread.joinable()) {
			m_thread.join();
		}		
	}
};




int main() {

	ThreadWrapper th;
	th.startThread();

	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}