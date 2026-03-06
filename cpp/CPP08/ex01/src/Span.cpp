#include "Span.hpp"

Span::Span() : maxStorage_(0)
{
	std::cout << "Default constructor called!" << std::endl;
}

Span::Span(unsigned int N) : maxStorage_(N)
{
	std::cout << "Constructor called!" << std::endl;
}

Span::Span(const Span &other) : maxStorage_()
{
	std::cout << "Copy constructor called!" << std::endl;
	this->maxStorage_ = other.maxStorage_;
	this->numberList_ = other.numberList_;
}

Span &Span::operator=(const Span &other)
{
	std::cout << "Copy assignment operator called!" << std::endl;
	if (this == &other)
		return *this;
	this->maxStorage_ = other.maxStorage_;
	this->numberList_ = other.numberList_;
	return *this;
}

Span::~Span() { std::cout << "Destructor called!" << std::endl; }

void Span::addNumber(int number)
{
	if (this->numberList_.size() + 1 > this->maxStorage_)
		throw maxCapacityException();
	this->numberList_.push_back(number);
}

int Span::longestSpan()
{
	if (this->numberList_.size() < 2)
		throw noSpanFound();

	return abs(*std::max_element(this->numberList_.begin(), this->numberList_.end()) -
						 *std::min_element(this->numberList_.begin(), this->numberList_.end()));
}

int Span::shortestSpan()
{
	if (this->numberList_.size() < 2)
		throw noSpanFound();

	std::vector<int> sorted = this->numberList_;
	std::sort(sorted.begin(), sorted.end());

	int minDiff = abs(sorted[1] - sorted[0]);
	for (size_t i = 1; i < sorted.size() - 1; ++i)
	{
		int diff = abs(sorted[i + 1] - sorted[i]);
		if (diff < minDiff)
			minDiff = diff;
	}
	return minDiff;
}

void Span::addRandomNumbers(unsigned int quantity)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	while (quantity > 0)
	{
		int randomNum = std::rand() - RAND_MAX / 2;
		this->addNumber(randomNum);
		std::cout << "Random number added: " << randomNum << std::endl;
		quantity--;
	}
}

const char *Span::maxCapacityException::what() const throw()
{
	return "[Exception] Exceeded size of vector.";
}

const char *Span::noSpanFound ::what() const throw()
{
	return "[Exception] No Span was found.";
}
