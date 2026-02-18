#include "Bureaucrat.hpp"

static void printSep() {
	std::cout << "-----------------------------" << std::endl;
}

int main() {
	// 1. Construction with grade too high
	std::cout << "Test 1: grade too high (0)" << std::endl;
	try {
		Bureaucrat b("Alpha", 0);
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 2. Construction with grade too low
	std::cout << "Test 2: grade too low (151)" << std::endl;
	try {
		Bureaucrat b("Beta", 151);
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 3. Decrement below minimum (grade 150)
	std::cout << "Test 3: decrement from 150" << std::endl;
	try {
		Bureaucrat b("Gamma", 150);
		std::cout << b << std::endl;
		b.decrementGrade();
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 4. Increment above maximum (grade 1)
	std::cout << "Test 4: increment from 1" << std::endl;
	try {
		Bureaucrat b("Delta", 1);
		std::cout << b << std::endl;
		b.incrementGrade();
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 5. Normal operations: increment and decrement
	std::cout << "Test 5: normal increment/decrement" << std::endl;
	try {
		Bureaucrat b("Epsilon", 5);
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << "After increment: " << b << std::endl;
		b.decrementGrade();
		b.decrementGrade();
		std::cout << "After two decrements: " << b << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 6. Copy constructor and assignment
	std::cout << "Test 6: copy and assignment" << std::endl;
	try {
		Bureaucrat original("Zeta", 42);
		Bureaucrat copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy:     " << copy << std::endl;
		Bureaucrat assigned("Eta", 100);
		assigned = original;
		std::cout << "Assigned: " << assigned << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	// 7. Default constructor
	std::cout << "Test 7: default constructor" << std::endl;
	try {
		Bureaucrat b;
		std::cout << b << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printSep();

	return 0;
}
