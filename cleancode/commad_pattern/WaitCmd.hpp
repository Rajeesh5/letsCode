#ifndef WAITCMD_HPP__
#define WAITCMD_HPP__

#include "ICommand.hpp"
#include <chrono>
#include <thread>
class WaitCommand : public Command {
public:
    explicit WaitCommand(const unsigned int durationInMilliseconds) noexcept ;
    void execute() override;
private:
    unsigned int durationInMilliseconds { 1000 };
};

#endif