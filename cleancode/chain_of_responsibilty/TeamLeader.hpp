#ifndef TEAMLEADER_HPP
#define TEAMLEADER_HPP

#include "LeaveHandler.hpp"

class TeamLeader : public LeaveHandler {
public:
    std::string applyLeave(const Leave& leave) override {
        if (leave.getNumberOfDays() <= 7) {
            if (leave.getEmpTier() <= 4) {
                return "Your leave days have been APPROVED by TeamLeader";
            } else {
                return "Your employee Tier level is too low for request " + std::to_string(leave.getNumberOfDays()) + " days";
            }
        } else {
            return superVisor->applyLeave(leave);
        }
    }
};

#endif // TEAMLEADER_HPP
