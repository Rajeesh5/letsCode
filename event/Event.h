#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <functional>
#include <sys/eventfd.h>
#include <unistd.h>
using namespace std;

typedef std::function<void(const std::string name)> userCallback;

class Event
{
    public:
        Event();
       ~Event();
       int getEventFd();
       void callback();
       void trigger();
       void setData(const string str);
       void registerCallback(userCallback cb);
    private:
       int m_eventFd;
       string m_data;
       userCallback m_cb;
};

#endif
