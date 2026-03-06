#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

class Span
{
private:
	unsigned int maxStorage_;
	std::vector<int> numberList_;
	Span();

public:
	explicit Span(unsigned int N);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();
	void addNumber(int number);
	template <typename InputIterator>
	void addNumbers(InputIterator begin, InputIterator end);
	int longestSpan();
	int shortestSpan();
	void addRandomNumbers(unsigned int quantity);
	class maxCapacityException : public std::exception
	{
		const char *what() const throw();
	};
	class noSpanFound : public std::exception
	{
		const char *what() const throw();
	};
};

template <typename InputIterator>
void Span::addNumbers(InputIterator begin, InputIterator end)
{
	for (InputIterator it = begin; it != end; ++it)
	{
		this->addNumber(*it);
	}
}
