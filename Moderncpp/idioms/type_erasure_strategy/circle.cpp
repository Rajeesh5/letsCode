#include "circle.hpp"

double Circle::GetRedious() const noexcept { return radious_; }
double Circle::GetParameter() const noexcept { return 2 * kPI * radious_; }