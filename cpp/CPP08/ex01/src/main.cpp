#include "Span.hpp"

int main()
{
	// Test 1: Basic add and random numbers
	Span obj(102);
	try
	{
		obj.addNumber(111);
		obj.addNumber(119);
		obj.addRandomNumbers(100);
		std::cout << "[Test 1] Longest Span is = " << obj.longestSpan() << std::endl;
		std::cout << "[Test 1] Shortest Span is = " << obj.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 1] " << e.what() << std::endl;
	}

	// Test 2: Add 10,000 numbers at once
	try
	{
		Span bigSpan(10000);
		std::vector<int> bigVec;
		for (int i = 0; i < 10000; ++i)
			bigVec.push_back(i * 2); // Even numbers
		bigSpan.addNumbers(bigVec.begin(), bigVec.end());
		std::cout << "[Test 2] Longest Span (should be 19998): " << bigSpan.longestSpan() << std::endl;
		std::cout << "[Test 2] Shortest Span (should be 2): " << bigSpan.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 2] " << e.what() << std::endl;
	}

	// Test 3: Exception on overflow
	try
	{
		Span smallSpan(2);
		smallSpan.addNumber(1);
		smallSpan.addNumber(2);
		smallSpan.addNumber(3); // Should throw
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 3] " << e.what() << std::endl;
	}

	// Test 4: Exception on not enough numbers
	try
	{
		Span emptySpan(10);
		emptySpan.addNumber(42);
		std::cout << emptySpan.shortestSpan() << std::endl; // Should throw
	}
	catch (std::exception &e)
	{
		std::cout << "[Test 4] " << e.what() << std::endl;
	}

	return 0;
}

/*
int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	return 0;
}*/
