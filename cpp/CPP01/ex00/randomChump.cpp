#include "Zombie.hpp"

void randomChump(const std::string& name) {
	Zombie random(name);
	random.announce();
}