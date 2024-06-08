#ifndef HELLOWORLDCMD_HPP__
#define HELLOWORLDCMD_HPP__

#include"ICommand.hpp"

class HelloWorldOutputCommand : public Command {
public:
    void execute() override;
};
#endif 