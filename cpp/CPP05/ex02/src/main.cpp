#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
	try {
		Bureaucrat gardener("Gardener", 137);
		ShrubberyCreationForm shrubbery("home");
		std::cout << shrubbery << std::endl;
		shrubbery.beSigned(gardener);
		std::cout << shrubbery << std::endl;
		gardener.executeForm(shrubbery);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: RobotomyRequestForm (success/fail) ===" << std::endl;
	try {
		Bureaucrat surgeon("Surgeon", 45);
		RobotomyRequestForm robotomy("Bender");
		robotomy.beSigned(surgeon);
		surgeon.executeForm(robotomy);
		surgeon.executeForm(robotomy);
		surgeon.executeForm(robotomy);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat president("President", 5);
		PresidentialPardonForm pardon("Arthur Dent");
		pardon.beSigned(president);
		president.executeForm(pardon);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Execute without signing ===" << std::endl;
	try {
		Bureaucrat worker("Worker", 1);
		ShrubberyCreationForm unsigned_form("garden");
		worker.executeForm(unsigned_form);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Execute with insufficient grade ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 100);
		Bureaucrat boss("Boss", 20);
		PresidentialPardonForm vip_pardon("VIP Person");
		vip_pardon.beSigned(boss);
		intern.executeForm(vip_pardon);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Sign with insufficient grade ===" << std::endl;
	try {
		Bureaucrat lowly("Lowly", 150);
		RobotomyRequestForm robot("Target");
		robot.beSigned(lowly);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}