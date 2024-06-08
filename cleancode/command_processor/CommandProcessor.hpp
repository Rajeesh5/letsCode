#ifndef CMD_PROCESSOR__
#define CMD_PROCESSOR__

#include <stack>
#include "Revertable.hpp"

class CommandProcessor {
public:
    void execute(const CommandPtr& command) ;
    void undoLastCommand();
private:
    std::stack<std::shared_ptr<Revertable>> commandHistory;
};
#endif

