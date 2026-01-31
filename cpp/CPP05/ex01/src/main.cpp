#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << "=== Test 1: Valid signing ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 50);
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;
		taxForm.beSigned(alice);
		std::cout << taxForm << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Grade too low to sign ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 100);
		Form vipForm("VIP Form", 50, 25);
		std::cout << vipForm << std::endl;
		vipForm.beSigned(bob);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Invalid form grade (too high) ===" << std::endl;
	try {
		Form invalidForm("Invalid", 0, 50);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Invalid form grade (too low) ===" << std::endl;
	try {
		Form invalidForm("Invalid", 50, 151);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Multiple signing attempts ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 1);
		Form permit("Building Permit", 10, 5);
		std::cout << permit << std::endl;
		permit.beSigned(charlie);
		std::cout << permit << std::endl;
		permit.beSigned(charlie);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}