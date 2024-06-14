#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

class Room {
 public:
  Room(const std::string& name);
  const std::string& getName() const;

 private:
  std::string name;
};

#endif  // ROOM_H
