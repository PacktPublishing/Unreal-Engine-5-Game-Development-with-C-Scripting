#pragma once

#include "Calculator.h"

class CalculatorEx : public Calculator
{
public:

	CalculatorEx();			//This is the constructor

	template <typename T>
	T Subtract(T a, T b)
	{
		return a - b;
	}
};