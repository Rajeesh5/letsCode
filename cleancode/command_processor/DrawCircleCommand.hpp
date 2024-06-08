#ifndef DRAW_CIRCLE_CMD__
#define DRAW_CIRCLE_CMD__

#include "Command.hpp"
#include "DrawingProcessor.hpp"
#include "Point.hpp"
#include "Revertable.hpp"

class DrawCircleCommand : public UndoableCommand {
public:
    DrawCircleCommand() = delete;
    DrawCircleCommand(DrawingProcessor& receiver, const Point& centerPoint, const double radius) noexcept;
    void execute() override ;
    void undo() override ;
private:
    DrawingProcessor& receiver;
    const Point centerPoint;
    const double radius;
};

#endif
