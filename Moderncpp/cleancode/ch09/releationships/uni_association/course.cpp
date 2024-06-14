#include "course.hpp"

Course::Course(const std::string& name) : name(name) {}

const std::string& Course::getName() const { return name; }
