#ifndef PROJECTLEADER_HPP
#define PROJECTLEADER_HPP

#include "LeaveHandler.hpp"

class ProjectLeader : public LeaveHandler {
public:
    std::string applyLeave(const Leave& leave) override {
        if (leave.getNumberOfDays() <= 14) {
            if (leave.getEmpTier() <= 3) {
                return "Your leave days have been APPROVED by Project Leader";
            } else {
                return "Your employee Tier level is too low for request " + std::to_string(leave.getNumberOfDays()) + " days";
            }
        } else {
            return superVisor->applyLeave(leave);
        }
    }
};

#endif // PROJECTLEADER_HPP
