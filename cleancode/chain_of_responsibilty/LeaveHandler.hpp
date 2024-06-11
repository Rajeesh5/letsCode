#ifndef LEAVEHANDLER_HPP
#define LEAVEHANDLER_HPP

#include <memory>
#include <string>
#include "Leave.hpp"

class LeaveHandler {
public:
    virtual ~LeaveHandler() = default;
    
    void setSuperVisor(std::shared_ptr<LeaveHandler> superVisor) {
        this->superVisor = superVisor;
    }

    virtual std::string applyLeave(const Leave& leave) = 0;

protected:
    std::shared_ptr<LeaveHandler> superVisor;
};

#endif // LEAVEHANDLER_HPP
