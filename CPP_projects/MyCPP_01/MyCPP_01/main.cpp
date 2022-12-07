#include <iostream>
#include "Calculator.h"

int main()
{
	std::cout << "MyCPP_01: Hello world! \n";

	Calculator Calculator;

	Calculator.Add(1.0f, 2.0f);
	Calculator.Subtract(10.0f, 5.0f);

	return 0;
}
