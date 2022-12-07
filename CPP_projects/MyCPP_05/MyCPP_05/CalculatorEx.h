#pragma once

#include "Calculator.h"

class CalculatorEx : public Calculator
{
public:

	CalculatorEx();			//This is the constructor

	int Subtract(int a, int b);

	float Subtract(float a, float b);
};