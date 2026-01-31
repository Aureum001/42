#include "ScavTrap.hpp"

int main(void) {
	std::cout << "=== Creating ClapTrap ===" << std::endl;
	ClapTrap clap("Clappy");
	
	std::cout << "\n=== Creating ScavTrap ===" << std::endl;
	ScavTrap scav("Scavvy");
	
	std::cout << "\n=== Testing ScavTrap ===" << std::endl;
	scav.attack("target");
	scav.takeDamage(30);
	scav.beRepaired(20);
	scav.guardGate();
	
	std::cout << "\n=== Testing ClapTrap ===" << std::endl;
	clap.attack("enemy");
	clap.takeDamage(5);
	clap.beRepaired(3);
	
	std::cout << "\n=== Copy Construction ===" << std::endl;
	ScavTrap scavCopy(scav);
	
	std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
	return 0;
}