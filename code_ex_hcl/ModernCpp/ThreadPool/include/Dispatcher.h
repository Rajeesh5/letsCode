#pragma once
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "abstract_request.h"
#include "Worker.h"
#include <queue>
#include <mutex>
#include <thread>
#include <vector>

class Dispatcher {
	static std::queue<AbstractRequest*> requestQ;
	static std::queue<Worker*> workerQ;
	static std::mutex requestQ_mutex;
	static std::mutex workerQ_mutex;
	static std::vector<Worker*> allWorkers;
	static std::vector<std::thread*> threads;
public:
	static bool init(int workers);
	static bool stop();
	static void addRequest(AbstractRequest* request);
	static bool addWorker(Worker* worker);
};
#endif