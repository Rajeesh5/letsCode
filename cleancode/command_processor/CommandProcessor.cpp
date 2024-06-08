#include "CommandProcessor.hpp"

void CommandProcessor::execute(const CommandPtr& command) {
    command->execute();
    commandHistory.push(command);
}
void CommandProcessor::undoLastCommand() {
    if (commandHistory.empty()) {
        return;
    }
    commandHistory.top()->undo();
    commandHistory.pop();
}


