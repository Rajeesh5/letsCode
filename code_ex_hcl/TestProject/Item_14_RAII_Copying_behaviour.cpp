#include <iostream>
#include <mutex>


// Resource-managing classes not only ment for to manage heap based memeory aquisition/release

class Lock {

public:
	explicit Lock(std::mutex* mu) :m_mutex(mu) {
		lock();
	}

	~Lock() {
		unlock();
	}
	void lock() { m_mutex->lock(); } 				// lock mutex pointed to by pm
	void unlock() { m_mutex->unlock(); } 			// unlock the mutex

private:
	std::mutex *m_mutex;

};

// Clients use Lock in the conventional RAII fashion :

void function() {
	std::mutex m; 						// define the mutex you need to use
										// create block to define critical section
	Lock ml(&m);		 				// lock the mutex
										// perform critical section operations
}                                       // automatically unlock mutex at end of block



class Lock1 {
public:

	void lock(std::mutex *m_mutex) { m_mutex->lock(); } 				
	void unlock() { 
		std::mutex *m_mutex = mutexPtr.get();
		m_mutex->unlock(); 
	} 			             

	explicit Lock1(std::mutex* pm) 			// init shared_ptr with the Mutex
		: mutexPtr(pm, unlock) 			    // to point to and the unlock function
	{ 							            // as the deleter
		lock(mutexPtr.get()); 			    // Get the raw pinter on Mutex.
	}
private:
	std::tr1::shared_ptr<std::mutex> mutexPtr; 	// use shared_ptr instead of raw 
	// pointer
};
