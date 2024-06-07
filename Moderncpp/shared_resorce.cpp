#include <iostream>
#include <memory>
#include <string>

class Person {
 public:
  Person(const int age, const std::string &name) : age_(age), name_(name) {}
  void ShowInfo() {
    std::cout << "Name: " << name_ << " Age: " << age_ << std::endl;
  }
  Person(const Person &p) : age_(p.age_), name_(p.name_) {
    std::cout << "Copy constructor called" << std::endl;
  }
  // Person(Person &&p) = delete;

 private:
  int age_;
  std::string name_;
};

void ShowPerson(Person p) {
  // Do something with p
  p.ShowInfo();
}

int main() {
  Person p1(23, "John");
  ShowPerson(std::move(p1));
}