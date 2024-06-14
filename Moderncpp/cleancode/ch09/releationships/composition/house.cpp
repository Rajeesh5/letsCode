#include "house.hpp"

House::House(const std::string& address) : address(address) {}

House::~House() {
  // Rooms are automatically cleaned up because of unique_ptr
}

void House::addRoom(const std::string& roomName) {
  rooms.push_back(std::make_unique<Room>(roomName));
}

const std::string& House::getAddress() const { return address; }

void House::printRooms() const {
  std::cout << "House at " << address
            << " has the following rooms:" << std::endl;
  for (const auto& room : rooms) {
    std::cout << "- " << room->getName() << std::endl;
  }
}
