#include <chrono>
#include <iostream>
#include <set>
#include <string>

std::multiset<std::string> names;  // global data structure

void log(const std::chrono::system_clock::time_point& now,
         const std::string& message) {
  // Logging function (implementation omitted)

  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
  std::cout << now_time_t << " " << message << std::endl;
}

void logAndAdd(const std::string& name) {
  auto now = std::chrono::system_clock::now();
  log(now, "logAndAdd");  // make log entry
  names.emplace(name);    // add name to global data structure
}

std::string nameFromIdx(int idx) {  // returns name corresponding to idx
  return std::to_string(idx);
}
void logAndAdd(int idx) {
  auto now = std::chrono::system_clock::now();
  log(now, "logAndAdd");
  names.emplace(nameFromIdx(idx));
}

class Person {
 public:
  template <typename T>
  explicit Person(T&& n)
      : name(std::forward<T>(n)) {}  // perfect forwarding ctor

  Person(const Person& rhs) = default;  // copy ctor (compiler-generated)
  Person(Person&& rhs) = default;       // move ctor (compiler-generated)

 private:
  std::string name;
};

int main() {
  std::string petName("Darla");
  logAndAdd(petName);                    // pass lvalue std::string
  logAndAdd(std::string("Persephone"));  // pass rvalue std::string
  logAndAdd("Patty Dog");                // pass string literal

  short nameIdx = 22;
  logAndAdd(nameIdx);  // Error!

  for (auto& item : names) {
    std::cout << item << std::endl;
  }

  Person p("Nancy");
  auto cloneOfP(p);  // Error!
  Person p1(22);

  return 0;
}
