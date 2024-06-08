
#include"Server.hpp"
#include <iostream>

void Server::acceptCommand(const CommandPtr& command) {   
    command->execute();
}