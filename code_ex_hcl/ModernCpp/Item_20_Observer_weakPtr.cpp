#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Observer {
public:
    virtual void Update() = 0;
};

class Subject { //As Observable

public:
    virtual void Subscribe(const std::shared_ptr<Observer>& observer) = 0;
    virtual void Unsubscribe(const std::shared_ptr<Observer>& observer) = 0;
    virtual void Notify() = 0;
};

class Gadget :public Observer {
public:
    Gadget(string name) :m_name(name) {}
    void Update() override {
        cout << m_name << " has Update" << endl;
    }
private:
    string m_name;
};

class WeatherStation :public Subject {

public:

    WeatherStation() = default;

    void Subscribe(const std::shared_ptr<Observer> &observer) override {
        m_observers.push_back(observer);
    }
    void Unsubscribe(const std::shared_ptr<Observer> &observer) override {
        m_observers.erase(
            std::remove_if( m_observers.begin(), m_observers.end(),
                [&](const std::weak_ptr<Observer>& wptr) {
                    return wptr.expired() || wptr.lock() == observer;
                }),
            m_observers.end()
       );
    }
    void Notify() override {
        for (auto item : m_observers) {
            if (!item.expired()) {
                auto observer = item.lock();
                observer->Update();
            }
        }
    }

private:
    std::vector<std::weak_ptr<Observer>> m_observers;

};


int main() {

    shared_ptr<Observer> g1 = make_shared<Gadget>("Mobile-1");
    shared_ptr<Observer> g2  (new Gadget("Mobile-2"));
    shared_ptr<Observer> g3  (new Gadget("Mobile-3"));

    
    WeatherStation station;

    station.Subscribe(g1);
    station.Subscribe(g2);
    station.Subscribe(g3);

    station.Notify();
    g2 = nullptr;               // g2 lifecycle end.
    
    station.Unsubscribe(g2);

    station.Notify();


}

