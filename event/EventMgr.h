#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include <algorithm>
#include <vector>
#include <map>

using func_ptr = void (*)(int); 
//function<void *(int)> fp;

class EventManager {

private:
   /*   
        Our events object would store “event_name” as the key and 
        std::vector of function pointers as value. Below is a sample 
        structure of our events object, where f1, f2, f3, f4, and f5 
        are pointers to functions.
        
        func_ptr = void foo(int);
        type_of func_ptr = void(*)(int)

         "event1": [fp1, fp2, fp3],  
         "event2": [fp4, fp5]    
    */

    std::map<std::string, std::vector<void (*)(int)> > events;

public:
    EventManager() {}

    void registerEvent(std::string event_name, func_ptr callback) {

        // we're using a pointer to reference `events[event_name]` so as
        // to get reference to original object and not the copy object.
        std::vector<void (*)(int)> *listeners = &events[event_name];

        // if this listener is already registered, we wont add it again
        if (std::find(listeners->begin(), listeners->end(), callback) != listeners->end()) {
          return;
        }

        listeners->push_back(callback);
    }

    bool fireEvent(std::string event_name, int arg) {
        std::vector<void (*)(int)> listeners = events[event_name];

        if (listeners.size() == 0) return false;

        // Run all the listeners associated with the event
        for (int idx = 0; idx < listeners.size(); idx += 1) {
            listeners[idx](arg);
        }

        return true;
    }
};

/*
    EventManager *on(std::string event_name, void (*callback)(int))
  
    This method will take in an event_name along with a callback and register this 
    callback as one of the listeners to the event. It’ll return a pointer to itself.
    This will help us chain the method calls. 
    
    Eg -> event_manager->on(..)->on(..)->emit(..)
    
    bool emit(std::string event_name, int arg)

    This method will take an event_name and an argument. This will invoke all the 
    listeners that are associated with this event and will return true if emitting
    succeeded. It’ll pass the arg to our callback functions.
*/

#endif