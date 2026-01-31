#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
	Intern someRandomIntern;

	std::cout << "=== Test 1: Create RobotomyRequest ===" << std::endl;
	try {
		Form* robotomy = someRandomIntern.makeForm("RobotomyRequest", "Bender");
		Bureaucrat surgeon("Surgeon", 45);
		robotomy->beSigned(surgeon);
		surgeon.executeForm(*robotomy);
		delete robotomy;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Create ShrubberyCreation ===" << std::endl;
	try {
		Form* shrubbery = someRandomIntern.makeForm("ShrubberyCreation", "garden");
		Bureaucrat gardener("Gardener", 137);
		shrubbery->beSigned(gardener);
		gardener.executeForm(*shrubbery);
		delete shrubbery;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Create PresidentialPardon ===" << std::endl;
	try {
		Form* pardon = someRandomIntern.makeForm("PresidentialPardon", "Arthur Dent");
		Bureaucrat president("President", 5);
		pardon->beSigned(president);
		president.executeForm(*pardon);
		delete pardon;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Unknown form type ===" << std::endl;
	try {
		Form* unknown = someRandomIntern.makeForm("UnknownForm", "target");
		delete unknown;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Alternative form names ===" << std::endl;
	try {
		Form* test1 = someRandomIntern.makeForm("robotomy request", "Test");
		if (test1) {
			std::cout << "Created: " << test1->getName() << std::endl;
			delete test1;
		}
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}