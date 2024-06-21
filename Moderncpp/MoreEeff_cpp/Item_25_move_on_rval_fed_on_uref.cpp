#include <iostream>
#include <memory>
#include <string>

class Widget {
 public:
  Widget() = default;
  Widget(Widget&& rhs) noexcept  // rhs is an rvalue reference
      : name(std::move(rhs.name)), id(std::move(rhs.id)) {
    std::cout << "Move constructor called\n";
  }

  template <typename T>
  void setName(T&& newtype) {
    type = std::forward<T>(newtype);  // Perfect forwarding
  }

  std::string getName() const { return name; }

 private:
  std::string name;
  std::string type;
  std::shared_ptr<int> id;
};



// The `std::move` function is used to cast an lvalue to an rvalue.
void PrintWidget(Widget&& w) {
  // std::cout << "Widget name: " << std::move(w).getName() << std::endl;
   std::cout << "Widget name: " << w.getName() << std::endl;
}

int main() {
  Widget w1;

  w1.setName("Hello");
  PrintWidget(std::move(w1));  // Moves resources from w1 to PrintWidget

  Widget w2(std::move(w1));  // Moves resources from w1 to w2
  return 0;
}
