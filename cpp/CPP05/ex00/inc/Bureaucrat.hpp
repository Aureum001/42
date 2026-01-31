#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

#define MAX_GRADE 1
#define MIN_GRADE 150

class Bureaucrat {
private:
	std::string const name_;
	unsigned int grade_;

public:
	Bureaucrat();
	Bureaucrat(std::string const &name, int const &grade);
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);
	~Bureaucrat();
	void incrementGrade();
	void decrementGrade();
	std::string getName() const;
	unsigned int getGrade() const;

	class GradeTooHighException : public std::exception {
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj);

#endif