#include "Dog.hpp"

Dog::Dog() : Animal() {
	this->type = "Dog";
	this->DogBrain = new Brain();
	std::cout << "Dog -> Default constructor called!\n";
}

Dog::Dog(const Dog &other) : Animal(other) {
	std::cout << "Dog -> Copy constructor called!\n";
	this->DogBrain = new Brain(*other.DogBrain);
}

Dog &Dog::operator=(const Dog &other) {
	std::cout << "Dog -> Copy assigment operator called!\n";
	if (this == &other)
		return *this;
	Animal::operator=(other);
	delete this->DogBrain;
	this->DogBrain = new Brain(*other.DogBrain);
	return *this;
}

Dog::~Dog() {
	delete this->DogBrain;
	std::cout << "Dog -> Destructor called!\n";
}

void Dog::makeSound() const {
	std::cout << "I am a auf auf auffff...." << std::endl;
}
