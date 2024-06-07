#include "square.hpp"

double Square::GetArea() const noexcept { return side_ * side_; }
double Square::GetParameter() const noexcept { return 4 * side_; }