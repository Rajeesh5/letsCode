#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

#include<vector>
using namespace std;

class ThreadPool {

public:
	void print(int tid) {

		while (i > 0 && isReady) {
			unique_lock<mutex> lock(mtx);
			// wake if thread id is currentThreadTurnId OR don’t 
			// have to wait to print anymore.
			cv.wait(lock, [&]() { 
				return ( tid == currentRunningThreadId || i==0 ) ;  });

			if (i==0) {				// Done now.
				lock.unlock();      // unlock the mutex.
				cv.notify_all();    // Notify all thread 
				break;              // time to exit from print.
			}

			cout << "Thread id :: " << tid << " : " << i-- << endl;
			currentRunningThreadId = currentRunningThreadId % NUMBER_OF_THREAD + 1;
			lock.unlock();			// Complementry, before notify.
			cv.notify_all();
		}
	}

	ThreadPool() {
		threads.push_back(thread(&ThreadPool::print,this,1)),
		threads.push_back(thread(&ThreadPool::print,this,2)),
		threads.push_back(thread(&ThreadPool::print,this,3)),
		threads.push_back(thread(&ThreadPool::print,this,4)),
		threads.push_back(thread(&ThreadPool::print,this,5));
	}
	
	void start() { isReady = true; }
	~ThreadPool() {
		for (auto& th : threads) {
			if (th.joinable()) {
				th.join();
			}
		}
	}

private:
	bool isReady{false};
	std::vector<thread> threads;
	const int NUMBER_OF_THREAD = 5;
	int i = 25;
	mutex mtx;
	condition_variable cv;
	int currentRunningThreadId{ 1 };

};
int main() {

	ThreadPool th;
	th.start();
	return 0;
}
