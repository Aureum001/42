#include "easyfind.hpp"
#include <list>

int main()
{
	srand(time(NULL));

	// Test 1: Random vector, random search (original test)
	try
	{
		std::vector<int> vectorToCheck;
		for (int i = 0; i < 5; i++)
		{
			int randNum = rand() % 5;
			std::cout << "[Test 1] Added to the vector[" << i << "] > " << randNum << std::endl;
			vectorToCheck.push_back(randNum);
		}
		int randNumToBeFound = rand() % 7;
		std::cout << "[Test 1] Trying to find in the vector value >> " << randNumToBeFound << std::endl;
		easyfind(vectorToCheck, randNumToBeFound);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 1] " << e.what() << std::endl;
	}

	// Test 2: Value guaranteed to be present
	try
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		std::cout << "[Test 2] Searching for 3 in {1,2,3,4,5}" << std::endl;
		easyfind(v, 3);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 2] " << e.what() << std::endl;
	}

	// Test 3: Value guaranteed to be absent
	try
	{
		std::vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);
		std::cout << "[Test 3] Searching for 99 in {10,20,30}" << std::endl;
		easyfind(v, 99);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 3] " << e.what() << std::endl;
	}

	// Test 4: Empty container
	try
	{
		std::vector<int> v;
		std::cout << "[Test 4] Searching for 1 in empty vector" << std::endl;
		easyfind(v, 1);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 4] " << e.what() << std::endl;
	}

	// Test 5: Using std::list
	try
	{
		std::list<int> l;
		l.push_back(42);
		l.push_back(100);
		std::cout << "[Test 5] Searching for 100 in list {42,100}" << std::endl;
		easyfind(l, 100);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 5] " << e.what() << std::endl;
	}

	// Test 6: Not found in list
	try
	{
		std::list<int> l;
		l.push_back(1);
		l.push_back(2);
		std::cout << "[Test 6] Searching for 3 in list {1,2}" << std::endl;
		easyfind(l, 3);
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 6] " << e.what() << std::endl;
	}

	return 0;
}