#ifndef DRAWING_PROCESSOR_HPP
#define DRAWING_PROCESSOR_HPP

#include "Point.hpp"

class DrawingProcessor {
public:
void drawCircle(const Point& centerPoint, const double radius) ;
void eraseCircle(const Point& centerPoint, const double radius) ;
void drawRectangle(const double len, const double wid);
void eraseRectangle(const double len, const double wid);
// ...
};

#endif