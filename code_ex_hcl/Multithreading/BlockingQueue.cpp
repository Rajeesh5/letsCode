#include<queue>
#include<iostream>
#include<mutex>
#include<condition_variable>

using namespace std;


template<typename T>
class BlockingQueue {

	void push(T& value) {

	}

	void pop() {

	}

	T& front() {

	}

	T& back() {

	}

private:
	std::queue<T> m_queue;
	
};