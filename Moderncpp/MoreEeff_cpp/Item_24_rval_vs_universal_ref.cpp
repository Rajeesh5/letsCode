

#include <iostream>
#include <vector>

template <typename T>
void f(std::vector<T>&& param) {
  // Do something with param
  std::cout << "Function f called with rvalue reference" << std::endl;
}

template <typename T>
void g(T&& param) {
  // Do something with param
  std::cout << "Function g called with ";
  if constexpr (std::is_lvalue_reference<T>::value) {
    std::cout << "lvalue reference" << std::endl;
  } else {
    std::cout << "rvalue reference" << std::endl;
  }
}

int main() {
  std::vector<int> vec1 = {1, 2, 3};
  // f(vec1);           // Error: cannot bind lvalue to rvalue reference
  f(std::move(vec1));  // Okay: std::move converts vec1 to an rvalue

  g(vec1);             // lvalue passed to g
  g(std::move(vec1));  // rvalue passed to g
  return 0;
}
