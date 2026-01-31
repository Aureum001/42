#include "DiamondTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void) {
	std::cout << "=== Creating DiamondTrap ===" << std::endl;
	DiamondTrap diamond("Diamondy");
	
	std::cout << "\n=== Testing DiamondTrap ===" << std::endl;
	diamond.whoAmI();
	diamond.attack("target");
	diamond.takeDamage(50);
	diamond.beRepaired(30);
	
	std::cout << "\n=== Testing special abilities ===" << std::endl;
	diamond.guardGate();
	diamond.highFivesGuys();
	
	std::cout << "\n=== Copy DiamondTrap ===" << std::endl;
	DiamondTrap diamondCopy(diamond);
	diamondCopy.whoAmI();
	
	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
