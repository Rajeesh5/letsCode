#ifndef SQUARE_HPP_
#define SQUARE_HPP_

#include <memory>

#include "DrawSquareStrategy.hpp"
#include "shape.hpp"

class Square : public Shape {
 public:
  Square(double side, std::unique_ptr<DrawSquareStrategy> strategy)
      : side_(side), drawing_(std::move(strategy)) {}

  double GetArea() const noexcept;
  double GetParameter() const noexcept;

  void Draw() override { drawing_->Draw(*this); }

 private:
  double side_;
  std::unique_ptr<DrawSquareStrategy> drawing_;
};

#endif