#include "Bureaucrat.hpp"
#include "Form.hpp"

static void printSep() {
	std::cout << "-----------------------------" << std::endl;
}

int main() {
	// 1. Valid signing
	std::cout << "Test 1: valid signing" << std::endl;
	try {
		Bureaucrat alice("Alice", 50);
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;
		alice.signForm(taxForm);
		std::cout << taxForm << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 2. Grade too low to sign
	std::cout << "Test 2: grade too low to sign" << std::endl;
	try {
		Bureaucrat bob("Bob", 100);
		Form vipForm("VIP Form", 50, 25);
		std::cout << vipForm << std::endl;
		bob.signForm(vipForm);
		std::cout << vipForm << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 3. Form grade too high (0)
	std::cout << "Test 3: form grade too high (0)" << std::endl;
	try {
		Form invalid("Invalid", 0, 50);
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 4. Form grade too low (151)
	std::cout << "Test 4: form grade too low (151)" << std::endl;
	try {
		Form invalid("Invalid", 50, 151);
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 5. Signing already-signed form
	std::cout << "Test 5: double signing" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 1);
		Form permit("Building Permit", 10, 5);
		charlie.signForm(permit);
		std::cout << permit << std::endl;
		charlie.signForm(permit);
		std::cout << permit << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 6. Copy form
	std::cout << "Test 6: copy form" << std::endl;
	try {
		Bureaucrat dave("Dave", 1);
		Form original("Original", 5, 5);
		dave.signForm(original);
		Form copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy:     " << copy << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	return 0;
}
