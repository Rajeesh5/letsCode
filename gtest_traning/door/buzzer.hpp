#ifndef BUZZER_HPP_
#define BUZZER_HPP_

#include "ibuzzer.hpp"

class Buzzer :public IBuzzer{
    public:
    void makeNoise(int interval) override;
};

#endif