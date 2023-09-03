#include<iostream>
#include<thread>
#include<queue>
#include<mutex>


using namespace std;


class ThreadWrapper{
private:
	std::thread *m_pthread;        // Producer thread
	std::thread *m_cthread;        // consumer thread
	std::deque<int> m_queue;       // container
	std::mutex m_mutex;
	std::condition_variable m_cv;

		
	bool isReady;
	int count;
public:
	ThreadWrapper() :isReady(false),m_pthread(nullptr),m_cthread(nullptr),count(10) {	
		isReady = true;	
	}
	
	void StartThreads();
	
	void Producer(){		

		while (count > 0)
		{
			std::unique_lock<std::mutex> locker(m_mutex);
			m_queue.push_front(count);						
			cout << "Produced data:: " << count << endl;
			count--;
			m_cv.notify_one();
			m_cv.wait(locker);
		}
	}
	
	void Concumer(){
		int data = 0;
		

		while (data != 1) {
			std::unique_lock<std::mutex> locker(m_mutex);
			m_cv.wait(locker, [&]() {
				return (!m_queue.empty());
				});
						
			data = m_queue.back();
			m_queue.pop_back();
			cout << "Consumed data:: " << data << endl;
			m_cv.notify_one();				// This line has huge improtance, need to find out.

			
		}
	}
	~ThreadWrapper();
};

void ThreadWrapper::StartThreads() {
	if (isReady) {
		m_pthread = new std::thread(&ThreadWrapper::Producer, this);
		m_cthread = new std::thread(&ThreadWrapper::Concumer, this);
	}
}

ThreadWrapper::~ThreadWrapper() {
	
	if (m_pthread->joinable()) {
		m_pthread->join();
	}
	if (m_cthread->joinable()) {
		m_cthread->join();
	}

	delete m_pthread;
	delete m_cthread;
	isReady = false;

}


int main_pc() {

	ThreadWrapper threads;
	threads.StartThreads();

	return 0;
}