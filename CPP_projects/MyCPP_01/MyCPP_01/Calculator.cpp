#include "Calculator.h"

float Calculator::Add(float a, float b)
{
	float result = a + b;
	OutputResult(a, " + ", b, result);
	return result;
}

float Calculator::Subtract(float a, float b)
{
	float result = a - b;
	OutputResult(a, " - ", b, result);
	return result;
}

void Calculator::OutputResult(float a, std::string op, float b, float result)
{
	std::cout << "Calculator: "
		<< a << op << b << " = " << result << "\n";
}
