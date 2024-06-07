#include <iostream>
#include <random>
#include <vector>

class Square {
  double side;

 public:
  Square(double side) : side(side) {}
  const char* getName() const { return "Square"; }
  double getArea() const { return side * side; }
};

// Implementation of Rectangle
class Rectangle {
  double length;
  double width;

 public:
  Rectangle(double length, double width) : length(length), width(width) {}
  const char* getName() const { return "Rectangle"; }
  double getArea() const { return length * width; }
};

// Implementation of Circle
class Circle {
  double radius;

 public:
  Circle(double radius) : radius(radius) {}
  const char* getName() const { return "Circle"; }
  double getArea() const { return 3.14159 * radius * radius; }
};

class DrawShape {
  class MyShape {
   public:
    virtual const char* getName() const = 0;
    virtual double getArea() const = 0;
    virtual ~MyShape() {}
  };

  // Wrapper
  template <typename T>
  class ShapeWrapper : public MyShape {
    const T* m_Shape;

   public:
    ShapeWrapper(const T* shape) : m_Shape(shape) {}

    const char* getName() const override { return m_Shape->getName(); }

    double getArea() const override { return m_Shape->getArea(); }
  };

  // Shape list
  std::vector<MyShape*> m_Shapes;

 public:
  template <typename T>
  void addShape(T* shape) {
    m_Shapes.push_back(new ShapeWrapper<T>(shape));
  }

  void drawShape() {
    size_t index = rand() % m_Shapes.size();
    std::cout << "Draw a " << m_Shapes[index]->getName() << " with an area of "
              << m_Shapes[index]->getArea() << std::endl;
  }
};

int main() {
  // Seed the random number generator
  srand(static_cast<unsigned int>(time(nullptr)));

  // Create shapes
  Square square(5.0);
  Rectangle rectangle(4.0, 6.0);
  Circle circle(3.0);

  // Create DrawShape instance and add shapes
  DrawShape drawer;
  drawer.addShape(&square);
  drawer.addShape(&rectangle);
  drawer.addShape(&circle);

  // Draw shapes randomly
  for (int i = 0; i < 5; ++i) {
    drawer.drawShape();
  }

  return 0;
}