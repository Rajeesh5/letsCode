#include <iostream>
#include "HelloWorldCmd.hpp"

void HelloWorldOutputCommand::execute() {
    
    std::cout << "Hello World!" << "\n";
}
