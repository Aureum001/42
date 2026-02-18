#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

static const int MAX_GRADE = 1;
static const int MIN_GRADE = 150;

class Form;

class Bureaucrat {
private:
	std::string const name_;
	int grade_;

public:
	Bureaucrat();
	Bureaucrat(std::string const &name, int grade);
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);
	~Bureaucrat();

	void incrementGrade();
	void decrementGrade();
	void signForm(Form &form);
	std::string getName() const;
	int getGrade() const;

	class GradeTooHighException : public std::exception {
	public:
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif
