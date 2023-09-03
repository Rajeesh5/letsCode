#include<iostream>
#include<thread>
#include<queue>
#include<mutex>



using namespace std;

std::mutex mlock;



std::deque<int> m_queue;				

void Producer(int count) {	
	std::unique_lock<mutex> m_lock(mlock, std::defer_lock);
	while (count > 0) {
		m_lock.lock();
		m_queue.push_front(count);
		cout << "Produced data:: " << count << endl;
		m_lock.unlock();
		count--;
		this_thread::sleep_for(chrono::seconds(1));
	}
}
	
void Consumer(){
	int data = 0;
	std::unique_lock<mutex> m_lock(mlock, std::defer_lock);
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

// Problem with this code so many call with 
// consumer bad hit... because consumaer is mmuch faster
// thread then producer. 

// So beeter approch is, once producer produce the data then only 
// consumer start it otherwise will wait.

int main() {
	thread th1(Producer,10);
	thread th2(Consumer);
	th1.join();
	th2.join();
}