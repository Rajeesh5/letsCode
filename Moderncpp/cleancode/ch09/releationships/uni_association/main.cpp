#include "course.hpp"
#include "student.hpp"

int main() {
  // Creating instances of courses
  auto course1 = std::make_shared<Course>("Mathematics");
  auto course2 = std::make_shared<Course>("Physics");

  // Creating instances of students
  auto student1 = std::make_shared<Student>("Alice");
  auto student2 = std::make_shared<Student>("Bob");

  // Enrolling students in courses
  student1->enrollInCourse(course1);
  student1->enrollInCourse(course2);
  student2->enrollInCourse(course1);

  // Display enrolled courses for student1
  student1->printCourses();

  return 0;
}
