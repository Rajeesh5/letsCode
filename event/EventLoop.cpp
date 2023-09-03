#include <string.h>
#include "EventLoop.h"

EventLoop::EventLoop()
{
    cout<<"EventLoop::ctor\n";
    m_epollFd = epoll_create1(0);
    if(m_epollFd < 0)
    {
        cout<<"Epoll create failed: "<<strerror(errno)<<endl;
    }
}

EventLoop::~EventLoop()
{
    cout<<"EventLoop::dtor: "<<m_epollFd<<"\n";
    if(m_epollFd > 0)
    {
        close(m_epollFd);
    }
}

int EventLoop::addEvent(shared_ptr<Event> spEvent)
{
    int rc = -1;
    epoll_event ev = {0, {0}};
    ev.events = EPOLLIN;
    ev.data.fd = spEvent->getEventFd();
    rc = epoll_ctl(m_epollFd, EPOLL_CTL_ADD, spEvent->getEventFd(), &ev);
    if(rc >= 0)
    {
        //cout<<"event successfully added to loop: "<<spEvent->getEventFd()<<endl;
        m_eventVec.push_back(spEvent);
    }
    else
    {
        cout<<"Could not add event in loop: "<<strerror(errno);
    }
    return rc;
}

void EventLoop::removeEvent(shared_ptr<Event> spEvent)
{
    epoll_event ev = {0, {0}};
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = spEvent->getEventFd();
    int rc = epoll_ctl(m_epollFd, EPOLL_CTL_DEL, spEvent->getEventFd(), &ev);
    if(rc >= 0)
    {
        for(auto it = m_eventVec.begin(); it != m_eventVec.end(); ++it)
        {
            if((*it)->getEventFd() == spEvent->getEventFd())
            {
                m_eventVec.erase(it);
                break;
            }
        }
    }
    else
    {
        cout<<"could not remove event from loop: "<<strerror(errno)<<endl;
    }
}

void EventLoop::loop()
{
    cout<<"EventLoop::loop()\n";
    epoll_event ev;
    int indefinite_wait = -1;
    int rc = -1;
    do
    {
        if(m_eventVec.size() > 0)
        {
            rc = epoll_wait(m_epollFd, &ev, 1, indefinite_wait);
            for(auto it = m_eventVec.begin(); it != m_eventVec.end(); ++it)
            {
                if ((*it)->getEventFd() == ev.data.fd)
                {
                    (*it)->callback();
                    break;
                }
            }
        }
    }
    while(rc >= 0);
    cout<<"out of event loop\n";
}
