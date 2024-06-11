#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <memory>
#include <vector>

#include "Observer.hpp"

class Subject {
 public:
  void addObserver(const ObserverPtr& observerToAdd);
  void removeObserver(const ObserverPtr& observerToRemove);

 protected:
  void notifyAllObservers() const;
  bool isNotYetObservingThisSubject(const ObserverPtr& observerToAdd);

 private:
  std::vector<ObserverPtr> observers;
};

#endif  // SUBJECT_HPP