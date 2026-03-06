
#include <iostream>
#include <Array.hpp>
#include <string>

#define MAX_VAL 750
int main(int, char **)
{

	Array<int> numbers(MAX_VAL);
	int *mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}

	// SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}

	Array<int> emptyArray;
	std::cout << "Default constructed array size: " << emptyArray.size() << std::endl;
	std::cout << "numbers.size() = " << numbers.size() << std::endl;

	Array<int> assignTest;
	assignTest = numbers;
	bool assignOk = true;
	for (unsigned int i = 0; i < assignTest.size(); ++i)
	{
		if (assignTest[i] != numbers[i])
		{
			assignOk = false;
			break;
		}
	}
	std::cout << "Assignment operator test: " << (assignOk ? "OK" : "FAIL") << std::endl;

	const Array<int> &constNumbers = numbers;
	std::cout << "constNumbers[0] = " << constNumbers[0] << std::endl;

	Array<std::string> strArr(3);
	strArr[0] = "Hello";
	strArr[1] = "Array";
	strArr[2] = "Test";
	for (unsigned int i = 0; i < strArr.size(); ++i)
		std::cout << "strArr[" << i << "] = " << strArr[i] << std::endl;

	// Exception tests
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	delete[] mirror; //
	return 0;
}