
#include "DrawCircleCommand.hpp"


DrawCircleCommand::DrawCircleCommand(DrawingProcessor& receiver, const Point& centerPoint,
const double radius) noexcept :
    receiver { receiver }, centerPoint { centerPoint }, radius { radius } {}

void DrawCircleCommand::execute()  {
    receiver.drawCircle(centerPoint, radius);
}

void DrawCircleCommand::undo()  {
    receiver.eraseCircle(centerPoint, radius);
}
