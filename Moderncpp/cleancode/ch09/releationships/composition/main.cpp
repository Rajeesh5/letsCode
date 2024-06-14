#include "house.hpp"

int main() {
  // Create a house instance
  House myHouse("123 Maple Street");

  // Add rooms to the house
  myHouse.addRoom("Living Room");
  myHouse.addRoom("Kitchen");
  myHouse.addRoom("Bedroom");

  // Display rooms in the house
  myHouse.printRooms();

  return 0;
}
