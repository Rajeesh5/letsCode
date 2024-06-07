#include <string>

class IApiLogger {
public:
    virtual void write(const std::string &msg) = 0;
    virtual ~IApiLogger() {}
};