#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>

using namespace std;

class PrintEvenOdd {
public:
	PrintEvenOdd():isReady(false),m_count(0){}

	void run(){
		threads.push_back(std::move(thread(&PrintEvenOdd::PrintEven, this)));
		threads.push_back(std::move(thread(&PrintEvenOdd::PrintOdd, this)));
		isReady=true;
	}

	void PrintEven() {

		while (m_count <= 50) {
			if (isReady) {
				std::unique_lock<std::mutex> locker(m_mutex);				
				cout << "even :: " << m_count++ << endl;
				m_cv.notify_one();      // notify the odd thread 
				// release the mutex and block the even thread until
				// signlled by another (odd thread) one. 
				// Even no need to manually unlock the mutex. 
				m_cv.wait(locker, [this] { return m_count % 2 == 0; });	
			}			
		}
	}

	void PrintOdd() {
		while (m_count <= 50) {
			if (isReady) {				
				{
					std::unique_lock<std::mutex> locker(m_mutex);
					m_cv.wait(locker, [this] { return m_count % 2 == 1; });
					cout << "Odd :: " << m_count++ << endl;
				}					// RAII Approch, anyway unlock the mutex 
				m_cv.notify_one();	// before it going to die.
				
			}			
		}
	}

	~PrintEvenOdd() {
		for (auto &th : threads) {
			if (th.joinable()) {
				th.join();
			}
		}
	}

private:

	std::vector<thread> threads;
	bool isReady;
	mutex m_mutex;
	condition_variable m_cv;
	int m_count;
};


int main() {
	PrintEvenOdd app;
	app.run();
	return 0;
}