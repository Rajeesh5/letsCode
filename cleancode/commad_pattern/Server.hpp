#ifndef SERVER_HPP__
#define SERVER_HPP__


#include"ICommand.hpp"

class Server {
public:
    void acceptCommand(const CommandPtr& command);
};
#endif