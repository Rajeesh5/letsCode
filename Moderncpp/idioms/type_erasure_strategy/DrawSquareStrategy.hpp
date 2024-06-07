#ifndef SQUARE_STRATEGY_HPP_
#define SQUARE_STRATEGY_HPP_

class Square;

class DrawSquareStrategy {
 public:
  virtual ~DrawSquareStrategy() = default;
  virtual void Draw(const Square &square);
};
#endif