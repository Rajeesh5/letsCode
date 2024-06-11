#ifndef LEAVE_HPP
#define LEAVE_HPP

enum class ReasonType {
    REGULAR, CRITICAL, SPECIAL
};

class Leave {
public:
    Leave(int numberOfDays, int empTier, ReasonType reason)
        : numberOfDays(numberOfDays), empTier(empTier), reason(reason) {}

    int getNumberOfDays() const { return numberOfDays; }
    int getEmpTier() const { return empTier; }
    ReasonType getReason() const { return reason; }

private:
    int numberOfDays;
    int empTier;
    ReasonType reason;
};

#endif // LEAVE_HPP
