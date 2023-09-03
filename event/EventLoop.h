#ifndef EVENTLOPP_H
#define EVENTLOPP_H

#include <iostream>
#include <memory>
#include <vector>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>
#include "Event.h"
using namespace std;

class EventLoop
{
    public:
        EventLoop();
       ~EventLoop();
        int addEvent(shared_ptr<Event> spEvent);
        void removeEvent(shared_ptr<Event> spEvent);
        void loop();
    private:
        int m_epollFd;
        vector<shared_ptr<Event>> m_eventVec;
};

#endif
