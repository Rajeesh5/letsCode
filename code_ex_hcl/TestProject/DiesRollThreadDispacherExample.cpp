#include "Header.h"

#include <thread>
#include <mutex>

inline int randrange(int lo, int hi) {
	return rand() / (RAND_MAX / (hi - lo + 1)) + lo;
}

std::mutex mtx;


class Thread {
public:

	thread::id pid() const { return m_pid; }

	~Thread() {
		running = false;
		if (theThread->joinable())
			theThread->join();
	}
	void startThread() {
		// Don't start two threads on the same object
		if (running) return;
		// Create an CPP thread, using the static callback
		theThread = new std::thread(&Thread::dispatch, this);
		running = 1;
	}
protected:
	Thread() : running(0) {}
	virtual void code() = 0;

private:
	std::thread* theThread;
	bool running;

	static thread::id m_pid;
	static void dispatch(void* thread_obj) {
		m_pid = this_thread::get_id();
		((Thread*)thread_obj)->code();	// Call the actual OO thread code	
		delete (Thread*)thread_obj;		// After code() returns, kill the 
// thread object

	}
};
thread::id Thread::m_pid;

///////////////////////////////////////////////////////////////////////
// An example thread class
///////////////////////////////////////////////////////////////////////


class Dice : public Thread {
public:
	static void create(const char* dicename);
	~Dice() {
		std::cout << name.c_str() << " :: Dies\n";
	}

private:
	Dice(const char* dicename) : name(dicename) {}
	virtual void code();
	std::string name;
};

void Dice::create(const char* dicename) {
	(new Dice(dicename))->startThread();
}

void Dice::code() {
	std::unique_lock<std::mutex> locker(mtx);
	std::cout << "Started thread #" << pid() << " for " << name.c_str() << "\n";
	locker.unlock();

	srand(time(0));
	for (;;) {
		int val = randrange(1, 6);
		locker.lock();
		std::cout << name.c_str() << " rolled " << val << std::endl;
		locker.unlock();
		// wait up to 500 ms
		this_thread::sleep_for(chrono::milliseconds(randrange(100, 500)));
	}
}

///////////////////////////////////////////////////////////////////////
// Let's test!
///////////////////////////////////////////////////////////////////////

int main()
{
	{
		Dice::create("dice1");
		Dice::create("dice2");
		this_thread::sleep_for(chrono::seconds(5)); // roll dice for 5 seconds
	}
	return 0; // cleanup? what's cleanup?
}


