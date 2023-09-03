#include<iostream>



int priority() { return 0; };												// Reveal our processing priority.
class Widget {};

void processWidget(std::shared_ptr<Widget> pw, int priority) {}				// Do some processing on a dynamically allocated 
																			// Widget in accord with a priority


int main_ECC17() {
	//processWidget(new Widget(), priority());								//Wont complile, share_ptr wont take row pointer.
	processWidget(std::shared_ptr<Widget>(new Widget), priority());			//fine..

	// Abobe like has three operation:
	//	1. call prioriry() 
	//  2. execute new Widget()
	//  3. call the contr of share_ptr
	// Now oeder of execution is dependent on complier. what happen if new Widget() execute first
	// then call priority() which has exeception and causes memory leak.


	// Store newer objects in smart pointers in standalone statements. Failure to do this can lead to
	// subtle resource leaks when exceptions are thrown.

	std::shared_ptr<Widget> w(new Widget());
	processWidget(w, priority());

	return 0;
}