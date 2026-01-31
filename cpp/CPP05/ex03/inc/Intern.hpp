#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Form;
class PresidentialPardonForm;
class RobotomyRequestForm;
class ShrubberyCreationForm;

class Intern {
public:
	Intern();
	Intern(const Intern &other);
	Intern &operator=(const Intern &other);
	~Intern();
	static Form *makeForm(const std::string &formName,
												 const std::string &formTargetName);
	static Form *makePresidentialPardonForm(const std::string &target);
	static Form *makeRobotomyRequestForm(const std::string &target);
	static Form *makeShrubberyCreationForm(const std::string &target);
	class FormNotFound : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};

#endif