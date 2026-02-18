#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>

class Bureaucrat;

class Form {
private:
	std::string const name_;
	bool isSigned_;
	const int signGrade_;
	const int execGrade_;

public:
	Form();
	Form(const std::string &name, int signGrade, int execGrade);
	Form(const Form &other);
	Form &operator=(const Form &other);
	~Form();

	std::string getName() const;
	bool getSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;
	void beSigned(const Bureaucrat &signer);

	class GradeTooHighException : public std::exception {
	public:
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Form &f);

#endif
