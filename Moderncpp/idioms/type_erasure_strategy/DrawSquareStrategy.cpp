
#include <iostream>

#include "DrawCircleStrategy.hpp"
#include "square.hpp"

void DrawSquareStrategy::Draw(const Square &square) {
  std::cout << "Square Area:: " << square.GetArea() << std::endl;
  std::cout << "Square Parameter:: " << square.GetParameter() << std::endl;
}
