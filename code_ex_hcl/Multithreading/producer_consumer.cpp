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
	std::condition_variable cv;
		
	bool isReady;
	int count;
public:
	ThreadWrapper() :isReady(false),m_pthread(nullptr),m_cthread(nullptr),count(10) {	
		isReady = true;	
	}
	
	void StartThreads();
	
	void Producer(){
		std::unique_lock<std::mutex> m_lock(m_mutex,std::defer_lock);
		while (count > 0) {
			m_lock.lock();
			m_queue.push_front(count);
			cout << "Produced data:: " << count << endl;
			m_lock.unlock();
			count--;
			this_thread::sleep_for(chrono::seconds(1));
		}

		}
	
	void Concumer(){
		int data = 0;
		std::unique_lock<std::mutex> m_lock(m_mutex, std::defer_lock);
		while (data != 1) {
			m_lock.lock();
			
			if (!m_queue.empty()) {
				data = m_queue.back();
				m_queue.pop_back();
				cout << "Consumed data:: " << data << endl;
				m_lock.unlock();
			}
			else {
				cout << "consumer thread bad hit\n";
				m_lock.unlock();
			}
			this_thread::sleep_for(chrono::milliseconds(100));
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


int main() {

	ThreadWrapper threads;
	threads.StartThreads();

	return 0;
}