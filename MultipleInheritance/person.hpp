
#ifndef IPERSON_H
#define IPERSON_H
#include <iostream>

class IPerson {
    public:
    virtual void QuickThinker() = 0;
    virtual ~IPerson() =default;
};
#endif