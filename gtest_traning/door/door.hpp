#ifndef DOOR_HPP_
#define DOOR_HPP_

#include <iostream>
#include <string>

class Door {
public:
    virtual void open();
    virtual void close();
    std::string getCurrentStatus() const;
private:
    std::string status = "closed";
};
#endif
