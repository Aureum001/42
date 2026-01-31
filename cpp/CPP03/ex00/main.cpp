#include "ClapTrap.hpp"

int main(void) {
	ClapTrap robot1("R2-D2");
	ClapTrap robot2("C-3PO");
	
	std::cout << std::endl;
	robot1.attack("C-3PO");
	robot2.takeDamage(0);
	robot2.beRepaired(5);
	
	std::cout << std::endl;
	// Drain all energy
	for (int i = 0; i < 10; i++)
		robot1.attack("target");
	
	std::cout << std::endl;
	// Try to attack with no energy
	robot1.attack("target");
	robot1.beRepaired(10);
	
	std::cout << std::endl;
	// Take massive damage
	robot2.takeDamage(15);
	robot2.attack("target");
	robot2.beRepaired(10);
	
	std::cout << std::endl;
	return 0;
}