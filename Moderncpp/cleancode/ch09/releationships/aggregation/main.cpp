#include "player.hpp"
#include "team.hpp"

int main() {
  // Creating instances of players
  auto player1 = std::make_shared<Player>("Alice");
  auto player2 = std::make_shared<Player>("Bob");

  // Creating instance of team
  auto team = std::make_shared<Team>("Dream Team");

  // Adding players to the team
  team->addPlayer(player1);
  team->addPlayer(player2);

  // Display players in the team
  team->printPlayers();

  return 0;
}
