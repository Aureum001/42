#pragma once

#include <string>
#include <sstream>
#include <algorithm>

class bigint
{
	private:
		std::string str;
		void trim();
		void check_digits();
	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint &other);
		bigint(const std::string &s);
		bigint &operator=(const bigint &other);
		std::string getStr() const;
		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);
		bigint &operator++();
		bigint operator++(int);
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint &operator<<=(unsigned int n);
		bigint &operator>>=(unsigned int n);
		bigint operator<<(const bigint &other) const;
		bigint operator>>(const bigint &other) const;
		bigint &operator<<=(const bigint &other);
		bigint &operator>>=(const bigint &other);
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
		bool operator<(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>=(const bigint &other) const;
};
		std::ostream &operator<<(std::ostream &os, const bigint &other);