#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <vector>

// Mocking the compute functions
int computeSomeValue1() { return 1; }
int computeSomeValue2() { return 2; }
int computeDivisor(int a, int b) { return a + b; }

using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

// Mocking the addDivisorFilter function
void addDivisorFilter() {
  auto calc1 = computeSomeValue1();
  auto calc2 = computeSomeValue2();
  auto divisor = computeDivisor(calc1, calc2);
  filters.emplace_back([&](int value) { return value % divisor == 0; });
  filters.emplace_back([&divisor](int value) { return value % divisor == 0; });
}

// Mocking the workWithContainer function
template <typename C>
void workWithContainer(const C& container) {
  auto calc1 = computeSomeValue1();
  auto calc2 = computeSomeValue2();
  auto divisor = computeDivisor(calc1, calc2);
  if (std::all_of(container.begin(), container.end(),
                  [&](const auto& value) { return value % divisor == 0; })) {
    // all values are multiples of divisor
  } else {
    // at least one value isn't
  }
}

// Test case for main function
TEST(MainTest, AddDivisorFilterTest) {
  addDivisorFilter();
  ASSERT_EQ(filters.size(), 2);
}

// Test case for workWithContainer function
TEST(WorkWithContainerTest, AllValuesAreMultiplesOfDivisor) {
  std::vector<int> container = {2, 4, 6, 8, 10};
  workWithContainer(container);
  // Add your assertions here
}

TEST(WorkWithContainerTest, AtLeastOneValueIsNotMultipleOfDivisor) {
  std::vector<int> container = {2, 4, 7, 8, 10};
  workWithContainer(container);
  // Add your assertions here
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}