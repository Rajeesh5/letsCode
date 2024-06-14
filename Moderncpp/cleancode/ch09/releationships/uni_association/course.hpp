#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

class Course {
 public:
  explicit Course(const std::string& name);
  const std::string& getName() const;

 private:
  std::string name;
};

#endif  // COURSE_H
