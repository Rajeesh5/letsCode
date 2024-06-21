#include <iostream>

class Widget {
 public:
  explicit Widget(const std::string& name = "default") : name_(name) {}

  // Widget(Widget&& rhs) noexcept  // rhs is an rvalue reference
  //     : name_(std::move(rhs.name_)) {
  //   std::cout << "Move constructor called\n";
  // }

  Widget(const Widget& rhs) : name_(rhs.name_) {
    std::cout << "Copy constructor called\n";
  }

  template <typename T>
  void setName(T&& name) {
    name_ = std::forward<T>(name);  // Perfect forwarding
  }

  std::string getName() && {
    // This method is called when the Widget object is an rvalue.
    // It moves the internal string out.
    std::cout << "getName() &&\n";
    return std::move(name_);
  }

  std::string getName() const& {
    // This method is called when the Widget object is an lvalue.
    // It copies the internal string.
    std::cout << "getName() const&\n";
    return name_;
  }

 private:
  std::string name_;
};
/*
Explanation

    Template Parameter T: The template parameter T allows PrintWidget to accept
any type, whether it's an lvalue or rvalue.

    T&& w: This is a universal reference (also called a forwarding reference in
the context of a function template), which can bind to both lvalues and rvalues.

    std::forward<T>(w): The std::forward function is used to cast w to its
original value category. If w is an lvalue, it remains an lvalue. If w is an
rvalue, it is cast to an rvalue.

Benefits

    Preserves Value Category: By using std::forward, the function preserves
whether w was originally an lvalue or rvalue, ensuring that the correct version
of getName() is called. Flexibility: This approach works for both lvalue and
rvalue Widget objects, making PrintWidget more flexible.
*/
template <typename T>
void PrintWidget(T&& w) {
  std::cout << "Widget name: " << std::forward<T>(w).getName() << std::endl;
}

void PrintWidget_rval(Widget&& w) {
  // It has warning because `std::move` function is not being called on
  // the `Widget` object passed to the `PrintWidget` function.

  // if you don't explicitly use std::move or similar to cast w to an rvalue
  // inside the function, w will be treated as an lvalue. This means that if
  // the getName() method involves copying or otherwise handling the Widget's
  // resources, it will do so as if w were a regular lvalue, potentially leading
  // to unnecessary copies.
  std::cout << "Widget name: " << w.getName() << std::endl;
  std::cout << "Widget name: " << std::move(w).getName() << std::endl;
}

int main() {
  Widget w1;
  PrintWidget_rval(std::move(w1));
  Widget w2 = std::move(w1);
  const Widget& w3 = std::move(w2);

  w1.setName("Hello");

  PrintWidget(w1);        // lvalue
  PrintWidget(Widget());  // rvalue

  return 0;
}
