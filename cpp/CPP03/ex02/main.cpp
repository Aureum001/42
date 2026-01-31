#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void) {
	std::cout << "=== Creating ClapTrap ===" << std::endl;
	ClapTrap clap("Clappy");
	
	std::cout << "\n=== Creating ScavTrap ===" << std::endl;
	ScavTrap scav("Scavvy");
	
	std::cout << "\n=== Creating FragTrap ===" << std::endl;
	FragTrap frag("Fraggy");
	
	std::cout << "\n=== Testing FragTrap ===" << std::endl;
	frag.attack("target");
	frag.takeDamage(40);
	frag.beRepaired(20);
	frag.highFivesGuys();
	
	std::cout << "\n=== Testing ScavTrap ===" << std::endl;
	scav.attack("enemy");
	scav.guardGate();
	
	std::cout << "\n=== Testing ClapTrap ===" << std::endl;
	clap.attack("dummy");
	
	std::cout << "\n=== Copy FragTrap ===" << std::endl;
	FragTrap fragCopy(frag);
	fragCopy.highFivesGuys();
	
	std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
	return 0;
}