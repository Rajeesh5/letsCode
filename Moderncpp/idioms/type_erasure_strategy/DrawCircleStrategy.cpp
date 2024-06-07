
#include "DrawCircleStrategy.hpp"

#include <iostream>

#include "circle.hpp"

void DrawCircleStrategy::Draw(const Circle &circle) {
  std::cout << "Circle Redious:: " << circle.GetRedious() << std::endl;
  std::cout << "Circle Parameter:: " << circle.GetParameter() << std::endl;
}
