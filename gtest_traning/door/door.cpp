#include "door.hpp"


void Door::open () {
    status = "open";
}

void Door::close () {
    status = "close";
}

std::string Door::getCurrentStatus() const {
    return status;
}


