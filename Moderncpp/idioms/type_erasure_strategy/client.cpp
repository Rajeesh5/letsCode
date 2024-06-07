#include <memory>
#include <vector>

#include "circle.hpp"
#include "shape.hpp"
#include "square.hpp"

using Shapes = std::vector<std::unique_ptr<Shape>>;

void DrawAllShape(const Shapes &shapes) {
  for (const auto &shape : shapes) {
    shape->Draw();
  }
}

int main() {
  Shapes shapes;
  shapes.emplace_back(
      std::make_unique<Circle>(6.0, std::make_unique<DrawCircleStrategy>()));

  shapes.emplace_back(
      std::make_unique<Square>(6.0, std::make_unique<DrawSquareStrategy>()));

  DrawAllShape(shapes);
}