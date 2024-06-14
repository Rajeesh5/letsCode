#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "room.hpp"

class House {
 public:
  House(const std::string& address);
  ~House();  // Custom destructor to manage room cleanup
  void addRoom(const std::string& roomName);
  const std::string& getAddress() const;
  void printRooms() const;

 private:
  std::string address;
  std::vector<std::unique_ptr<Room>> rooms;  // Composition: House owns Rooms
};

#endif  // HOUSE_H
