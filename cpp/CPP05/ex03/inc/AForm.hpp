#ifndef AFORM_HPP
#define AFORM_HPP

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
	Form(const std::string &name, unsigned int signGrade,
				unsigned int execGrade);
	Form();
	Form(const Form &other);
	Form &operator=(const Form &other);
	virtual ~Form() = 0;
	std::string getName() const;
	bool getSigned() const;
	void setSigned(bool sign);
	unsigned int getSignGrade() const;
	unsigned int getExecGrade() const;
	void beSigned(Bureaucrat &signer);
	void execute(Bureaucrat const &executor) const;
	virtual void executer() const = 0;

	class GradeTooHighException : public std::exception {
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
		const char *what() const throw();
	};

	class FormIsNotSigned : public std::exception {
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Form &obj);

#endif
