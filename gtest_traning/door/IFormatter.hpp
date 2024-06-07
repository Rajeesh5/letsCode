#include <string>

class IFormatter {
    public:

     virtual std::string format(const std::string& input) =0;
};