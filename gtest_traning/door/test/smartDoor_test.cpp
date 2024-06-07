#include "smartDoor.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

using  testing::StrEq;

class FackLogger : public IApiLogger {
public:
    
    // Below code make smart class (mock)
    int writeCallCount = 0;
    std::string msgArg = "";
    void write(const std::string &msg) {
        writeCallCount++;
        msgArg = msg;
    }
    ~FackLogger () {}
};

// Only stub class
class FackBuzzer :public IBuzzer{
    public:
    void makeNoise(int interval) {}
    ~FackBuzzer() {}
};


TEST(SmartDoorTestSuit, OpenMethodTest) {

    // Note :: logger & buzzer are stub, those object are dependency
    // without that we cant call open()/ close() API.

    std::shared_ptr<FackLogger> logger = std::make_shared<FackLogger>();
    std::shared_ptr<FackBuzzer> buzzer = std::make_shared<FackBuzzer>();

    SmartDoor test_obj(logger, buzzer);


    test_obj.open();
    ASSERT_EQ (test_obj.getCurrentStatus(), "open");

    // Still open method not tested properly, we just tested Door::open() API
    // SmartDoor::open() has other respocibilty. 
    // Need to communicate with dependency/intraction 
    // such kind of testing called :: Behaviour/Interaction/communication testing 

    // stub : is a fack object which dont record interaction 
    // mock : is a fack object which record intreaction 
    
    //ASSERT_EQ(logger->writeCallCount, 1);

}



class MockLogger : public IApiLogger {
    public:
    MOCK_METHOD(void, write, (const std::string &msg));
    ~MockLogger() {}
};

class MockBuzzer : public IBuzzer {
    public:
    MOCK_METHOD(void, makeNoise, (int interval));
    ~MockBuzzer () {}
};

// Note::  you must set expection before intraction.


TEST(SmartDoorTestSuit, OpenMethodIntractionTesting) {

    std::shared_ptr<FackLogger> logger = std::shared_ptr<FackLogger>();
    std::shared_ptr<FackBuzzer> buzzer = std::shared_ptr<FackBuzzer>();

    SmartDoor test_obj(logger, buzzer);

    EXPECT_CALL(logger, write(StrEq("Door open"))).Times(1);
    
    // See below, mock without intraction, it will give the warning!!
    test_obj.open()
    ASSERT_EQ(test_obj.getCurrentStatus(), "open");

    // To remove the warning need to do the niceMock 
    // NiceMock<MockLogger> logger;
    // StrickMock<MockLogger> logger;
    // test_obj.open()
    // ASSERT_EQ(test_obj.getCurrentStatus(), "open");

}
