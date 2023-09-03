#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "EventLoop.h"
#include "Event.h"
using namespace std;

void EvCb(const std::string name)
{
    //cout<<std::this_thread::get_id()<<" EvCb called with name = "<<name<<endl;
    cout<<"EvCb called with name = "<<name<<endl;
}

void thread_ev1(shared_ptr<Event> sp)
{
    this_thread::sleep_for(chrono::seconds(1));
    while(true)
    {
        //cout<<std::this_thread::get_id()<<" Trigger\n";
        sp->setData("Event1");
        sp->trigger();
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void thread_ev2(shared_ptr<Event> sp)
{
    this_thread::sleep_for(chrono::seconds(2));
    while(true)
    {
        //cout<<std::this_thread::get_id()<<" Trigger\n";
        sp->setData("Event2");
        sp->trigger();
        this_thread::sleep_for(chrono::seconds(8));
    }
}

int main()
{
   EventLoop loop;
   shared_ptr<Event> spEv1 = make_shared<Event>();
   spEv1->registerCallback(std::bind(&EvCb, std::placeholders::_1));
   shared_ptr<Event> spEv2 = make_shared<Event>();
   spEv2->registerCallback(std::bind(&EvCb, std::placeholders::_1));
   loop.addEvent(spEv1);
   loop.addEvent(spEv2);
   std::thread t1(thread_ev1, spEv1);
   std::thread t2(thread_ev2, spEv2);
   //cout<<std::this_thread::get_id()<<" loop\n";
   loop.loop();
}
