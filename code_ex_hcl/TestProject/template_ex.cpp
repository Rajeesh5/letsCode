#include<iostream>

using namespace std;

class Widget {
public:
    Widget(){}
    virtual ~Widget(){}
    virtual size_t size() const {
        return 1;
    };
    virtual void normalize() {}
    void swap(Widget& other) {}
};

class NastyWidget : public Widget {
public:
    NastyWidget() {}
    virtual ~NastyWidget() {}
    size_t size() const { return 1; }
    void normalize() {}
};

class RandomType {
public:
    RandomType() {}
    virtual ~RandomType() {}
    RandomType size() const {
        RandomType tmp;
        // Some Size operations;
        return tmp;
    }

    bool operator > ( int x)    {
        return true;
    }

};


void doProcessing(Widget& w) {
    if (w.size() > 5) {
        w.normalize();
        w.swap(w);
    }
}

template<typename T>
void doProcessingTP(T& w)
{
    if (w.size() > 5) {
        w.normalize();
        w.swap(w);
    }
}



int main() {

    NastyWidget nw;
    doProcessingTP(nw);

    RandomType rt;
    doProcessingTP(rt);

}