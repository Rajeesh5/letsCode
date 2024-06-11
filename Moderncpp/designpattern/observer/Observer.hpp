#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <memory>

class Observer {
 public:
  virtual ~Observer() = default;
  virtual int getId() const noexcept = 0;
  virtual void update() = 0;
};

bool operator==(const Observer& lhs, const Observer& rhs);

using ObserverPtr = std::shared_ptr<Observer>;

#endif  // OBSERVER_HPP
