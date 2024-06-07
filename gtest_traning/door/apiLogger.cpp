#include "apiLogger.hpp"
#include <iostream>

void  ApiLogger::write(const std::string &msg) {
    std::cout << msg << std::endl;
}