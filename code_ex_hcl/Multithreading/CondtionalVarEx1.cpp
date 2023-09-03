#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std;

class MyPrinter {

public:

	MyPrinter(int threadCnt,const string &str, int cnt) {
		m_msg = str;
		m_charCnt = cnt;
		m_threadCnt = threadCnt;
		m_threadId = 0;
		m_nxtChar = 0;
		m_allowedThread = 0;
		m_isReady = false;
	}

	int getCurrentThreadID(const thread::id& num) {
		for (int index = 0; index < m_threadIds.size(); index++) {
			if (m_threadIds[index] == num) {
				return index;
			}
		}
		return -1;

	}

	// Logic for printing chars.
	void print_chars(){
		cout << "Thread id:: " << getCurrentThreadID(this_thread::get_id()) << ":";

	}

	void print_thread(){

		while (m_isReady && true ) {
			unique_lock<mutex> lock(m_mutex);
			m_cv.wait(lock, [this] { this_thread::get_id() == m_threadIds[m_allowedThread++]; });
			print_chars();

			if (m_allowedThread == m_threadIds.size()) {
				m_allowedThread = 0;
			}

			if (m_nxtChar >= m_msg.length()) {
				m_nxtChar -= m_msg.length();
			}
			lock.unlock();
			m_cv.notify_all();
		}
	
	}

	void run() {
		for (int i = 0; i < m_threadCnt; i++) {
			// thread th(&MyPrinter::print_thread, this);
			// m_threadPool.push_back(std::move(th));							   // Base on L-value			
			m_threadPool.push_back(std::thread(&MyPrinter::print_thread, this));   // Base on R-values
			m_threadIds.push_back(m_threadPool[i].get_id);			
		}
		m_isReady = true;
	}

	~MyPrinter() {
		for (auto& element : m_threadPool) {
			if (element.joinable()) {
				element.join();
			}
		}
	}

private:


	vector<thread> m_threadPool;
	vector<thread::id> m_threadIds;
	int m_threadCnt;
	string m_msg;
	int m_charCnt;
	condition_variable m_cv;
	mutex m_mutex;
	int m_threadId = 0;
	int m_nxtChar = 0;
	int m_allowedThread = 0;
	bool m_isReady;
};




int main() {

	MyPrinter print();



	return 0;
}