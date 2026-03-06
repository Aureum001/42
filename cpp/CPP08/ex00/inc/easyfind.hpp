#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

template <typename T> void easyfind(T container, int toBeFound);

class ValueNotFound : public std::exception {
  virtual const char *what() const throw();
};
#include "easyfind.tpp"
