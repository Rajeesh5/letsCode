#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Course;  // Forward declaration

class Student {
 public:
  explicit Student(const std::string& name);
  void enrollInCourse(const std::shared_ptr<Course>& course);
  const std::string& getName() const;
  void printCourses() const;

 private:
  std::string name;
  std::vector<std::shared_ptr<Course>> courses;
};

#endif  // STUDENT_H
