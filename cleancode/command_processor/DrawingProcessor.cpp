#include "DrawingProcessor.hpp"
#include <iostream>

void DrawingProcessor::drawCircle(const Point& centerPoint, const double radius) {
    std::cout << "drawing circle" << std::endl;
}
void DrawingProcessor::eraseCircle(const Point& centerPoint, const double radius) {
    std::cout << "ereasing circle" << std::endl;
}
void DrawingProcessor::drawRectangle(const double len, const double wid) {
    std::cout << "drawing rantangle" << std::endl;
}
void DrawingProcessor::eraseRectangle(const double len, const double wid) {
    std::cout << "ereasing rantangle" << std::endl;
}
