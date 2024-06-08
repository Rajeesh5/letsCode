#include "WaitCmd.hpp"

    WaitCommand::WaitCommand(const unsigned int durationInMilliseconds) noexcept :
    durationInMilliseconds{durationInMilliseconds} { };
    
    void WaitCommand::execute() {
        std::chrono::milliseconds timespan(durationInMilliseconds);
        std::this_thread::sleep_for(timespan);
    }