#pragma once

#include <iostream>

class Calculator
{
public : 
	float Add(float a, float b);
	float Subtract(float a, float b);
private:
	void OutputResult(float, std::string, float, float);
};