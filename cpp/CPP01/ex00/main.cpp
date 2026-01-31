#include "Zombie.hpp"

int main() {
	Zombie *heapZombie = newZombie("Heapnstein");
	heapZombie->announce();
	
	randomChump("Stackson");
	
	delete heapZombie;
	return (0);
}