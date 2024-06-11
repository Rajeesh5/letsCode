#include "Subject.hpp"

#include <algorithm>
#include <vector>

void Subject::addObserver(const ObserverPtr& observerToAdd) {
  if (isNotYetObservingThisSubject(observerToAdd)) {
    observers.push_back(observerToAdd);
  }
}
void Subject::removeObserver(const ObserverPtr& observerToRemove) {
  observers.erase(
      std::remove(observers.begin(), observers.end(), observerToRemove),
      observers.end());
}

void Subject::notifyAllObservers() const {
  for (const auto& observer : observers) {
    observer->update();
  }
}

bool Subject::isNotYetObservingThisSubject(const ObserverPtr& observerToAdd) {
  return std::find(observers.begin(), observers.end(), observerToAdd) ==
         observers.end();
}
