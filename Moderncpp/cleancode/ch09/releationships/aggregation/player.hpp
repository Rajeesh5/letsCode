#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>
#include <string>

class Player {
 public:
  Player(const std::string& name);
  const std::string& getName() const;

 private:
  std::string name;
};

#endif  // PLAYER_H
