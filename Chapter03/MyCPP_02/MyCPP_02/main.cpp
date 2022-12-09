#include <iostream>

int Add(int a, int b)
{
	return a + b;
}

void main()
{
	std::cout << "My Calculations" << std::endl;

	int result = Add(1, 2);
	std::cout << "Integer addition: 1 + 2 = " 
			  << result 
		      << std::endl;
	result = Add(3, 4);
	std::cout << "Integer addition: 3 + 4 = " 
		      << result 
		      << std::endl;

	std::cout << "Finished!";
}