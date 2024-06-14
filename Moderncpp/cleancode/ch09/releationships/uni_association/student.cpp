#include "student.hpp"

#include "course.hpp"

Student::Student(const std::string& name) : name(name) {}

void Student::enrollInCourse(const std::shared_ptr<Course>& course) {
  courses.push_back(course);
}

const std::string& Student::getName() const { return name; }

void Student::printCourses() const {
  std::cout << name << " is enrolled in:" << std::endl;
  for (const auto& course : courses) {
    std::cout << "- " << course->getName() << std::endl;
  }
}
