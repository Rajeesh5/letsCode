#ifndef DRAW_RACTANGLE_CMD__
#define DRAW_RACTANGLE_CMD__

#include "Command.hpp"
#include "DrawingProcessor.hpp"
#include "Point.hpp"
#include "Revertable.hpp"

class DrawRectangleCommand : public UndoableCommand {
public:
    DrawRectangleCommand() = delete;
    DrawRectangleCommand(DrawingProcessor& receiver, const double len, const double wid) ;
    void execute() override ;
    void undo() override ;
private:
    DrawingProcessor& receiver;
    double length;
    double width;
};

#endif
