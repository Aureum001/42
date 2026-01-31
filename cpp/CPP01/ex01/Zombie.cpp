#include "Zombie.hpp"

Zombie::Zombie() : name("unnamed") {
}

void Zombie::announce() {
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

void Zombie::setName(const std::string& inputName) {
	name = inputName;
}

Zombie::~Zombie() {
	std::cout << name << " destroyed\n";
}