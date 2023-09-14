#include "EventMgr.h"
#include <iostream>

void callback1(int num) {
	std::cout << "\n";
	std::cout << "callback1-" << num * 2;
}

void callback2(int num) {
	std::cout << "\n";
	std::cout << "callback2-" << num/2 << std::endl;
}

int main() {

    std::string event_nm = "test_event";
	EventManager *event_manager = new EventManager(); 



	event_manager->registerEvent(event_nm, callback1);      // Need to pass topic number
    event_manager->registerEvent(event_nm, callback2);

    // { test_event -> [callback1, collback2] }

	if(event_manager->fireEvent(event_nm, 100)) {
        std::cout << "Event Fired :: " << event_nm << std::endl; 
    }


    if(!event_manager->fireEvent("bad_event", 200)) {
        std::cout << "Event not found" << std::endl;
    }
	
	return 0;
}