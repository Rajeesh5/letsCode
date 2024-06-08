#include <iostream>
#include "CommandProcessor.hpp"
#include "DrawCircleCommand.hpp"
#include "DrawRectangleCommand.hpp"
#include "Point.hpp"
#include "DrawingProcessor.hpp"

int main() {
    // Initialize the drawing processor
    DrawingProcessor drawingProcessor;

    // Initialize the command processor
    CommandProcessor commandProcessor;

    // Create points for drawing
    Point centerPoint1; // Assume Point class has a suitable constructor or set methods
    Point centerPoint2;

    // Define the radius and dimensions
    double radius1 = 10.0;
    double radius2 = 15.0;
    double length = 20.0;
    double width = 10.0;

    // Create commands
    auto drawCircleCommand1 = std::make_shared<DrawCircleCommand>(drawingProcessor, centerPoint1, radius1);
    auto drawCircleCommand2 = std::make_shared<DrawCircleCommand>(drawingProcessor, centerPoint2, radius2);
    auto drawRectangleCommand = std::make_shared<DrawRectangleCommand>(drawingProcessor, length, width);

    // Execute commands
    commandProcessor.execute(drawCircleCommand1);
    commandProcessor.execute(drawCircleCommand2);
    commandProcessor.execute(drawRectangleCommand);

    // Undo commands
    commandProcessor.undoLastCommand(); // Undo rectangle
    commandProcessor.undoLastCommand(); // Undo second circle
    commandProcessor.undoLastCommand(); // Undo first circle

    return 0;
}