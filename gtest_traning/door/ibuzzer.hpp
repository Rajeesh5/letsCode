#ifndef IBUZZER_HPP_
#define IBUZZER_HPP_

#include <iostream>

class IBuzzer {
    public:
    virtual void makeNoise(int interval)=0;
    virtual ~IBuzzer() {}
};

#endif