#ifndef HR_HPP
#define HR_HPP

#include "LeaveHandler.hpp"

class HR : public LeaveHandler {
public:
    std::string applyLeave(const Leave& leave) override {
        if (leave.getNumberOfDays() <= 21) {
            if (leave.getEmpTier() <= 3 && leave.getReason() != ReasonType::REGULAR) {
                return "Your leave days have been APPROVED by HR";
            } else {
                return "Your leave request has been DENIED by HR";
            }
        } else {
            return superVisor->applyLeave(leave);
        }
    }
};

#endif // HR_HPP
