#include "StringCalculator.hpp"
#include <iostream>

int main()
{
	StringCalculator calulator;
	int result = calulator.Add("1,2//5_");
	std::cout << "Result = " << result << std::endl;
	return 0;
}