#include <gtest/gtest.h>
#include "door.hpp"



TEST(DoorTestSuite, ReturnClosebyDefault) {
    
    // Arrange
    Door door;        
    std::string expect_value = "close";
    
    // Act
	std::string current_value = door.getCurrentStatus();
    
    // Assert
    ASSERT_EQ(expect_value, current_value);
}

TEST(DoorTestSuite, ReturnClose) {
    
    // Arrange
    Door door;        
    std::string expect_value = "close";
    door.close();
    
    // Act
	std::string current_value = door.getCurrentStatus();
    
    // Assert
    ASSERT_EQ(expect_value, current_value);
}

TEST(DoorTestSuite, ReturnOpen) {
    
    // Arrange
    Door door;        
    std::string expect_value = "open";
    door.open();
    
    // Act
	std::string current_value = door.getCurrentStatus();
    
    // Assert
    ASSERT_EQ(expect_value, current_value);
}

