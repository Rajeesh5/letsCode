#include "Observer.hpp"

bool operator==(const Observer& lhs, const Observer& rhs) {
  return lhs.getId() == rhs.getId();
}
