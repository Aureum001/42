#pragma once

#include <exception>
#include <iostream>
#include <cstdlib>
#include <ctime>

template <class T>
class Array
{
private:
	T *array_;
	unsigned int size_;

public:
	Array();
	Array(unsigned int n);
	Array(const Array &other);
	Array &operator=(const Array &other);
	~Array();
	unsigned int size() const;
	T &operator[](unsigned int i);
	T operator[](unsigned int i) const;
	class OutOfRange : public std::exception
	{
		const char *what() const throw();
	};
};

#include "Array.tpp"