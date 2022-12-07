#include "Calculator.h"

Calculator::Calculator()
{
	_name = "Addition Calculator";
}

string Calculator::GetName()
{
	return _name;
}

int Calculator::Add(int a, int b)
{
	return a + b;
}

float Calculator::Add(float a, float b)
{
	return a + b;
}
