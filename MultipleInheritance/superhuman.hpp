
#ifndef SPERSON_H
#define SPERSON_H
#include <memory>
#include "animal.hpp"
#include "person.hpp"

class SuperHuman : public IPerson, public IAnimal, public std::enable_shared_from_this<SuperHuman>{
public:
    virtual void Runner() override;
    virtual void QuickThinker() override;
    virtual ~SuperHuman() override { std::cout << "Deleted SuperHuman" << std::endl; }
private:
    int iq_power_ = 0;
    int running_speed_ =0;
};
#endif