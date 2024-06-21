#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

int computeSomeValue1() { return 1; }
int computeSomeValue2() { return 2; }
int computeDivisor(int a, int b) { return a + b; }

using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

void addDivisorFilter() {
  auto calc1 = computeSomeValue1();
  auto calc2 = computeSomeValue2();
  auto divisor = computeDivisor(calc1, calc2);
  filters.emplace_back([&](int value) { return value % divisor == 0; });

  filters.emplace_back([&divisor](int value) { return value % divisor == 0; });

}  // divisor will dangle!

template <typename C>
void workWithContainer(const C& container) {
  auto calc1 = computeSomeValue1();
  auto calc2 = computeSomeValue2();
  auto divisor = computeDivisor(calc1, calc2);

  if (std::all_of(container.begin(), container.end(),
                  [&](const auto& value) { return value % divisor == 0; })) {
    std::cout << "All values are multiples of divisor" << std::endl;
  } else {
    std::cout << "At least one value isn't" << std::endl;
  }
}

class Widget {
 public:
  explicit Widget(int divisor) : divisor(divisor) {}
  void addFilter() const;

 private:
  int divisor;
};
/*
// Correct Approach
void Widget::addFilter() const {
  auto divisorCopy = divisor;
  filters.emplace_back(
      [divisorCopy](int value) { return value % divisorCopy == 0; });
}
*/

void doSomeWork() {
  auto pw = std::make_unique<Widget>(2);
  pw->addFilter();
}  // Widget is destroyed, filter now has a dangling pointer!

/*

void Widget::addFilter() const {
    auto currentObjectPtr = this;
    filters.emplace_back([currentObjectPtr](int value) { return value %
currentObjectPtr->divisor == 0; });
}
*/

void addDivisorFilter() {
  static auto calc1 = computeSomeValue1();
  static auto calc2 = computeSomeValue2();
  static auto divisor = computeDivisor(calc1, calc2);
  filters.emplace_back([=](int value) { return value % divisor == 0; });
  ++divisor;
}

int main() {
  // addDivisorFilter();

  // std::vector<int> container = {3, 6, 9, 12, 15};
  // workWithContainer(container);

  doSomeWork();
  if (filters[0](100)) {
    std::cout << "100 is multiple of 2" << std::endl;
  }

  return 0;
}
