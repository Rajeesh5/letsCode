#include "IFormatter.hpp"

class DefaultFormatter: public IFormatter {
    public:
    std::string format(const std::string& input) override{ return input; }
}