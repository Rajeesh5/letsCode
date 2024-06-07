#include <gtest/gtest.h>
#include "StringCalculator.hpp"

class StringCalculatorAddTestSuiteFixture : public ::testing::Test {

protected:
    StringCalculator *calulatorObj;

    void SetUp() override {         // before each test case
        calulatorObj = new StringCalculator();
        std::cout << "SetUp\n";
    }
    void TearDown() override {      // after each test case   
        delete calulatorObj;
        std::cout <<"Teardown\n";
    }
    static void SetUpTestSuite() {  //Before Each testsuite
        // 
        std::cout << "static SetUp\n";
    }     
    static void TearDownTestSuite() {  //After each Testsuite
        std::cout <<"static Teardown\n";
    }
};


/*   Data Driven test-case (parameterized value testing)
   
   INPUT           EXPECTED_VALUE
   -----           --------------
   ""					0
   "1,2"				3
   "-1"					invalid_argument  --not supported 
   "1,,2,1//"			4
*/

class StringCalculatorParameterFixture : public StringCalculatorAddTestSuiteFixture ,
                                         public testing::WithParamInterface<std::tuple<std::string,int>> {
};

INSTANTIATE_TEST_SUITE_P(ValueBasedAddTest,
                         StringCalculatorParameterFixture,
                         testing::Values( std::make_tuple("",0),
                                          std::make_tuple("1",1)
                                        ));


TEST_P(StringCalculatorParameterFixture, AddParameterizedTest) {

    std::string input = std::get<0>(GetParam());
    int expect_value  = std::get<1>(GetParam());

    int actualValue   = calulatorObj->Add(input);
    ASSERT_EQ(expect_value, actualValue);
}

// Demonstrate some basic assertions.
TEST_F(StringCalculatorAddTestSuiteFixture, BasicAssertions) {

	int result = calulatorObj->Add("1,2//5_");
    ASSERT_EQ(result,8);

}

TEST_F(StringCalculatorAddTestSuiteFixture, when_passed_negative_numbers) {   
    /*
        // Dont try this one: Gtest will not support, It will not retuen object of 
        // expection, but will type of exeption.

    try {
	    calulatorObj->Add("1,-2,-4,5");
    } catch( std::exception &e) {
	    ASSERT_EQ( e.what(), "Negatives not allowed: -2,-4");
    }
    */
    EXPECT_THROW(calulatorObj->Add("1,-2,-4,5"), invalid_argument);
}

// Demonstrate some basic assertions.
TEST_F(StringCalculatorAddTestSuiteFixture, BasicAssertionsOnlySeperator) {

	int result = calulatorObj->Add("1,");
    ASSERT_EQ(result,1);

}

TEST(StringCalculatorAddTestSuite, ReturnZeroForEmptyString) {
    
    // Arrange
    StringCalculator calulator;         
    int expect_value = 0;
    std::string input = "";
    
    // Act
	expect_value = calulator.Add(input);
    
    // Assert
    ASSERT_EQ(expect_value,0);
}

TEST(StringCalculatorAddTestSuite, CommaDelimitedNumbers) {
    
    // Arrange
    StringCalculator calulator;         
    int expect_value = 0;
    std::string input = "1,2,3";
    
    // Act
	expect_value = calulator.Add(input);
    
    // Assert
    ASSERT_EQ(expect_value, 6);
}

TEST(StringCalculatorAddTestSuite, WithSpicalChar) {
    
    // Arrange
    StringCalculator calulator;         
    int expect_value = 0;
    std::string input = "1,2\n\n,1//";
    
    // Act
	expect_value = calulator.Add(input);
    
    // Assert
    ASSERT_EQ(expect_value, 4);
}

TEST(StringCalculatorAddTestSuite, multiple_delimiters) {
    
    // Arrange
    StringCalculator calulator;         
    int expect_value = 0;
    std::string input = "//[*][%]\n4*2%3";
    
    // Act
	expect_value = calulator.Add(input);
    
    // Assert
    ASSERT_EQ(expect_value, 9);
}


