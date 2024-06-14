#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "player.hpp"

class Team {
 public:
  Team(const std::string& name);
  void addPlayer(const std::shared_ptr<Player>& player);
  const std::string& getName() const;
  void printPlayers() const;

 private:
  std::string name;
  std::vector<std::shared_ptr<Player>> players;
};

#endif  // TEAM_H
