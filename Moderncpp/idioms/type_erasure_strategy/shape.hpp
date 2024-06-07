#ifndef SHAPE_HPP_
#define SHAPE_HPP_

class Shape {
 public:
  Shape() = default;
  virtual ~Shape() = default;
  virtual void Draw() = 0;
};

#endif