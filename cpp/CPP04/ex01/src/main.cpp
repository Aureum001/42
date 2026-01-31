#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main() {
	std::cout << "=== Basic polymorphism test ===\n";
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;
	delete i;

	std::cout << "\n=== Deep copy test ===\n";
	Dog originalDog;
	{
		Dog copiedDog(originalDog);
		std::cout << "Copied dog going out of scope...\n";
	}
	std::cout << "Original dog still valid\n";

	std::cout << "\n=== Assignment operator test ===\n";
	Cat cat1;
	Cat cat2;
	cat2 = cat1;
	std::cout << "Both cats still valid\n";

	std::cout << "\n=== Array of Animals ===\n";
	const int SIZE = 10;
	Animal* animals[SIZE];
	for (int i = 0; i < SIZE / 2; i++)
		animals[i] = new Cat();
	for (int i = SIZE / 2; i < SIZE; i++)
		animals[i] = new Dog();
	
	std::cout << "\n=== Deleting all animals ===\n";
	for (int i = 0; i < SIZE; i++)
		delete animals[i];

	return 0;
}