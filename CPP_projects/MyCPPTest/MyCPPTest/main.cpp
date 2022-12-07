#include <iostream>
#include "Calculator.h"

int main()
{
	std::cout << "MyCPPTest: Hello world! \n";

	Calculator Calculator;

	Calculator.Add(1.0f, 2.0f);
	Calculator.Subtract(10.0f, 5.0f);

	return 0;
}