#pragma once

#include <exception>
#include <iostream>
#include <stack>
#include <string>

class RPN {
private:
  std::stack<float> _stack;

  RPN();

public:
  explicit RPN(const char *input);
  RPN(const RPN &other);
  RPN &operator=(const RPN &other);
  ~RPN();

  class DivisionByZero : public std::exception {
    const char *what() const throw();
  };

  class NotEnoughNumbers : public std::exception {
    const char *what() const throw();
  };

  class NotEnoughOperators : public std::exception {
    const char *what() const throw();
  };

  class InvalidToken : public std::exception {
    const char *what() const throw();
  };
};