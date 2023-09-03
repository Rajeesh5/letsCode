#include "Event.h"
#include <string.h>

Event::Event()
{
    cout<<"Event::Ctor\n";
    m_eventFd = eventfd(0,0);
}

Event::~Event()
{
    cout<<"Event::dtor\n";
    if(m_eventFd > 0)
    {
        close(m_eventFd);
    }
}

int Event::getEventFd()
{
    return m_eventFd;
}

void Event::callback()
{
    //cout<<"Event::callback: "<<m_eventFd<<endl;
    uint64_t val;
    read(m_eventFd, &val, sizeof(val));
    if(m_cb != nullptr)
    {
        m_cb(m_data);
    }
}

void Event::trigger()
{
    cout<<"Event::trigger: "<<m_eventFd<<endl;
    constexpr uint64_t val = 1;
    int rc = write(m_eventFd, &val, sizeof(val));
}

void Event::setData(const string str)
{
    m_data = str;
}

void Event::registerCallback(userCallback cb)
{
    m_cb = cb;
}
