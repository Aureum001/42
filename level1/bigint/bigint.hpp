#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint
{
private:
	std::string str;

	// normalize internal representation
	void trim();
	void check_digits();

public:
	bigint();
	bigint(unsigned int num);
	bigint(const std::string &s); // allow string input
	bigint(const bigint &source);

	std::string getStr() const;
	bigint &operator=(const bigint &source);

	// Addition
	bigint operator+(const bigint &other) const;
	bigint &operator+=(const bigint &other);

	// Increment
	bigint &operator++();	// ++x
	bigint operator++(int); // x++

	// Digit shift
	bigint operator<<(unsigned int n) const;
	bigint operator>>(unsigned int n) const;
	bigint &operator<<=(unsigned int n);
	bigint &operator>>=(unsigned int n);

	// Digit shift with bigint argument (used by provided main)
	bigint operator<<(const bigint &other) const;
	bigint operator>>(const bigint &other) const;
	bigint &operator<<=(const bigint &other);
	bigint &operator>>=(const bigint &other);

	// Comparison
	bool operator==(const bigint &other) const;
	bool operator!=(const bigint &other) const;
	bool operator<(const bigint &other) const;
	bool operator>(const bigint &other) const;
	bool operator<=(const bigint &other) const;
	bool operator>=(const bigint &other) const;
};

std::ostream &operator<<(std::ostream &output, const bigint &obj);

#endif // BIGINT_HPP
