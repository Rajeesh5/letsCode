#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <memory>

#include "DrawCircleStrategy.hpp"
#include "shape.hpp"

class Circle : public Shape {
 public:
  Circle(double radious, std::unique_ptr<DrawCircleStrategy> strategy)
      : radious_(radious), drawing_(std::move(strategy)) {}

  double GetRedious() const noexcept;
  double GetParameter() const noexcept;

  void Draw() override { drawing_->Draw(*this); }

 private:
  const double kPI = 3.14;
  double radious_;
  std::unique_ptr<DrawCircleStrategy> drawing_;
};

#endif