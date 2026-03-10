#include "RPN.hpp"

#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

RPN::RPN(const char *input)
{
	std::istringstream ss(input);
	std::string token;

	while (ss >> token)
	{
		if (token.size() == 1 && std::isdigit((unsigned char)token[0]))
		{
			_stack.push(static_cast<float>(token[0] - '0'));
		}
		else if (token.size() == 1 &&
						 (token[0] == '+' || token[0] == '-' ||
							token[0] == '*' || token[0] == '/'))
		{
			if (_stack.size() < 2)
				throw NotEnoughNumbers();
			const float b = _stack.top();
			_stack.pop();
			const float a = _stack.top();
			_stack.pop();
			switch (token[0])
			{
			case '+':
				_stack.push(a + b);
				break;
			case '-':
				_stack.push(a - b);
				break;
			case '*':
				_stack.push(a * b);
				break;
			case '/':
				if (b == 0.0f)
					throw DivisionByZero();
				_stack.push(a / b);
				break;
			}
		}
		else
		{
			throw InvalidToken();
		}
	}
	if (_stack.size() != 1)
		throw NotEnoughOperators();
	std::cout << _stack.top() << std::endl;
}

const char *RPN::DivisionByZero::what() const throw()
{
	return "Error: division by zero.";
}

const char *RPN::NotEnoughNumbers::what() const throw()
{
	return "Error: not enough numbers for operation.";
}

const char *RPN::NotEnoughOperators::what() const throw()
{
	return "Error: too many numbers, not enough operators.";
}

const char *RPN::InvalidToken::what() const throw()
{
	return "Error: invalid token in expression.";
}
