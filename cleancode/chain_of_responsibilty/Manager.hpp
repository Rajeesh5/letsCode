#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "LeaveHandler.hpp"

class Manager : public LeaveHandler {
public:
    std::string applyLeave(const Leave& leave) override {
        if (leave.getNumberOfDays() > 21) {
            if (leave.getEmpTier() <= 2 && leave.getReason() == ReasonType::SPECIAL) {
                return "Your leave days have been APPROVED by Manager";
            }
        }
        return "Your leave request has been DENIED by Manager";
    }
};

#endif // MANAGER_HPP
