#ifndef CIRCLE_STRATEGY_HPP_
#define CIRCLE_STRATEGY_HPP_

class Circle;

class DrawCircleStrategy {
 public:
  virtual ~DrawCircleStrategy() = default;
  virtual void Draw(const Circle &circle);
};
#endif