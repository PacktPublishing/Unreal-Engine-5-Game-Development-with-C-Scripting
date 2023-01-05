#pragma once

#include <iostream>

using namespace std;

class Calculator
{
protected:

	string _name;

public:
	Calculator();		//This is the constructor

	string GetName();


	/*
		Function Add: adds two values and returns the result
		Parameters a, b: the two input values
	*/
	template <typename T>
	T Add(T a, T b)
	{
		return a + b;
	}
};