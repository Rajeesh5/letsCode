#include "team.hpp"

Team::Team(const std::string& name) : name(name) {}

void Team::addPlayer(const std::shared_ptr<Player>& player) {
  players.push_back(player);
}

const std::string& Team::getName() const { return name; }

void Team::printPlayers() const {
  std::cout << name << " has the following players:" << std::endl;
  for (const auto& player : players) {
    std::cout << "- " << player->getName() << std::endl;
  }
}
