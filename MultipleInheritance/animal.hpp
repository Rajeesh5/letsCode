
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
class IAnimal {
    public:
    virtual void Runner() = 0;
    virtual ~IAnimal() =default;
};
#endif