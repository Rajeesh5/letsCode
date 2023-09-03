#include "dispatcher.h"
#include "request.h"
#include <iostream> 
#include <string> 
#include <csignal>
#include <thread> 
#include <chrono>

using namespace std;


sig_atomic_t signal_caught = 0; 
mutex logMutex;

void sigint_handler(int sig) { 
	signal_caught = 1; 
}

// The calculation() ("dummy") method is the method being passed to each request.
// Here we need to write actual logic in order of perform request processing.
// Code inside this method is mutually execusive for each request.


void calculation(string text) { 
	logMutex.lock();    
	cout << text << "\n";    
	logMutex.unlock(); 
}

int main() {
	signal(SIGINT, &sigint_handler);    
	
	Dispatcher::init(10);						//Initialzing Dispatcher, adding 10 Worker thread
												//into threadQ.
	cout << "Initialised.\n";        
	
	int taskID = 0;    
	Request* rq = 0;    
	while (!signal_caught && taskID < 50) {

		rq = new Request();						// Create 50 new Request.
		rq->setValue(taskID);					// Add unique taskID into it.
		rq->setOutput(&calculation);			// Performed rquest processing using Calculation method. 

		Dispatcher::addRequest(rq);             // Added request to dispatcher.
		taskID++;
	}
	this_thread::sleep_for(chrono::seconds(5)); 

	
	Dispatcher::stop();    
	cout << "Clean-up done.\n";
	return 0;
}