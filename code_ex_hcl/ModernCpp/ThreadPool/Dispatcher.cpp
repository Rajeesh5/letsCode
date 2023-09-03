#include "Dispatcher.h"
#include <iostream>

using namespace std;

queue<AbstractRequest*> Dispatcher::requestQ;
queue<Worker*> Dispatcher::workerQ;
mutex Dispatcher::requestQ_mutex;
mutex Dispatcher::workerQ_mutex;
vector<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;


bool Dispatcher::init(int workers) {
	for (int i = 0; i < workers; ++i) {
		Worker *worker = new Worker();
		allWorkers.push_back(worker);
		thread *thread_t = new thread(&Worker::run, worker);
		threads.push_back(thread_t);
	}
	return true;
}

bool Dispatcher::stop() {
	for (int i = 0; i < allWorkers.size(); ++i) {
		allWorkers[i]->stop();
	}
	cout << "Stopped workers.\n";
	for (int j = 0; j < threads.size(); ++j) {
		threads[j]->join();
		cout << "Joined threads.\n";
	}

	return true;
}

void Dispatcher::addRequest(AbstractRequest* request) 
{ 
	workerQ_mutex.lock();  
	if (!workerQ.empty()) 
	{ 
		Worker* worker = workerQ.front();
		worker->setRequest(request);
		worker->notify();
		workerQ.pop();
		workerQ_mutex.unlock();
	} 
	else 
	{ 
		workerQ_mutex.unlock();
		requestQ_mutex.lock();
		requestQ.push(request);
		requestQ_mutex.unlock();
	}
}

bool Dispatcher::addWorker(Worker* worker) {
	bool wait = true;
	requestQ_mutex.lock(); 
	if (!requestQ.empty()) 
	{ 
		AbstractRequest* request = requestQ.front();
		worker->setRequest(request);
		requestQ.pop();
		wait = false;
		requestQ_mutex.unlock();
	}
	else { 
		requestQ_mutex.unlock();
		workerQ_mutex.lock();
		workerQ.push(worker);
		workerQ_mutex.unlock();
	}            
	return wait;
}