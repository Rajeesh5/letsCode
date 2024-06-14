#include "player.hpp"

Player::Player(const std::string& name) : name(name) {}

const std::string& Player::getName() const { return name; }
