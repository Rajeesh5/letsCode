#ifndef API_LOGGER_HPP_
#define API_LOGGER_HPP_

#include "iLogger.hpp"

class ApiLogger : public IApiLogger {
public:
    void write(const std::string &msg) override;
};
#endif 