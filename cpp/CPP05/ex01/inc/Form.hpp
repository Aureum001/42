#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
private:
	std::string const name_;
	bool isSigned_;
	const unsigned int signGrade_;
	const unsigned int execGrade_;

public:
	Form(const std::string &name, unsigned int signGrade, unsigned int execGrade);
	Form();
	Form(const Form &other);
	Form &operator=(const Form &other);
	~Form();
	std::string getName() const;
	bool getSigned() const;
	unsigned int getSignGrade() const;
	unsigned int getExecGrade() const;
	void beSigned(Bureaucrat &signer);

	class GradeTooHighException : public std::exception {
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Form &obj);

#endif