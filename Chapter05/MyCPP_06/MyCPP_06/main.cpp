#include <iostream>
#include "Calculator.h"
#include "CalculatorEx.h"

using namespace std;

void main()
{
	//CalculatorEx calculator;	//defines the calculator object
	CalculatorEx *pCalculator = new CalculatorEx();
								//creates a new CalculatorEx instance and
								//store its address to the pCalculator pointer
	
	//cout << "My Calculations: " << calculator.GetName() << endl;
	cout << "My Calculations: " << pCalculator->GetName() << endl;

	float input1, input2;
	string operation;
	while (true)
	{
		cout << "Input the first value (0 to exit): ";
		cin >> input1;
		if (input1 == 0)	//exit if the user enters 0
		{
			break;
		}

		cout << "Input the second value (0 to exit): ";
		cin >> input2;
		if (input1 == 0)	//exit if the user enters 0
		{
			break;
		}

		operation = "+";
		do
		{
			cout << "Please choose the operation (+ or -): ";
			cin >> operation;
		} while (operation != "+" && operation != "-");

		int a = input1;
		int b = input2;
		if (a == input1 && b == input2)
		{
			int result;
			if (operation == "+")
			{
				//result = calculator.Add<int>(a, b);
				result = pCalculator->Add<int>(a, b);
				cout << "Integer addition: " << a << " + " << b << " = "
					<< result
					<< std::endl;
			}
			else
			{
				//result = calculator.Subtract<int>(a, b);
				result = pCalculator->Subtract<int>(a, b);
				cout << "Integer subtraction: " << a << " - " << b << " = "
					<< result
					<< std::endl;
			}
		}
		else
		{
			float result;
			if (operation == "+")
			{
				//result = calculator.Add<float>(input1, input2);
				result = pCalculator->Add<float>(input1, input2);
				cout << "float addition:  " << input1 << " + " << input2 << " = "
					<< result
					<< std::endl;
			}
			else
			{
				//result = calculator.Subtract<float>(input1, input2);
				result = pCalculator->Subtract<float>(input1, input2);
				cout << "float subtraction:  " << input1 << " - " << input2 << " = "
					<< result
					<< std::endl;
			}
		}
	}

	delete pCalculator;
	std::cout << "Finished!";
}
