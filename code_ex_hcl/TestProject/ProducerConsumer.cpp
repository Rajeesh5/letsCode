#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<deque>
#include<vector>
using namespace std;


class ProducerConsumer {
public:
	ProducerConsumer() :isReady(false), m_counter(10) {
		threads.push_back(std::move(thread(&ProducerConsumer::Producer,this)));
		threads.push_back(std::move(thread(&ProducerConsumer::Consumer, this)));
		isReady = true;
	}

	void Producer() {
		while (isReady && m_counter > 0) {
			std::unique_lock<mutex> locker(mu);
			m_queue.push_front(m_counter);
			cout << "Push Data::" << m_counter << endl;
			m_counter--;
			m_cv.notify_one();		//Notify waiting thread, if any.
			m_cv.wait(locker);		//sleep this thread, release mutex.
		}
	}

	void Consumer() {
		int data = 0;
		while (isReady && data != 1) {
			std::unique_lock<mutex> locker(mu);
			//sleep this thread and release the mutex, starts only once
			//conditional variable notify by producer thread. Once notified again 
			//acquire the mutex.

			m_cv.wait(locker, [=]() { return !m_queue.empty(); });
			data = m_queue.back();
			m_queue.pop_back();
			cout << "Data is::" << data << endl;
			m_cv.notify_one();
		}
	}

	~ProducerConsumer() {
		for (auto& th : threads) {
			if (th.joinable()) {
				th.join();
			}
		}
	}
private:
	std::mutex mu;
	std::condition_variable m_cv;
	std::vector<thread> threads;
	std::deque<int> m_queue;
	bool isReady;
	int m_counter;

};


int main() {
	ProducerConsumer prob;
	return 0;
}