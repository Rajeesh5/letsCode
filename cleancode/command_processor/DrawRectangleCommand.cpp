
#include "DrawRectangleCommand.hpp"


DrawRectangleCommand::DrawRectangleCommand(DrawingProcessor& receiver, const double len, const double wid)
    : receiver(receiver), length(len), width(wid) {}

void DrawRectangleCommand::execute() {
    receiver.drawRectangle(length, width);
}

void DrawRectangleCommand::undo() {
    receiver.eraseRectangle(length, width);
}