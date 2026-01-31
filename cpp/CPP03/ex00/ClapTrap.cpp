#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string& name) 
	: _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap " << _name << " constructed" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) 
	: _name(other._name), _hitPoints(other._hitPoints), 
		_energyPoints(other._energyPoints), _attackDamage(other._attackDamage) {
	std::cout << "ClapTrap " << _name << " copy constructed" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &other) {
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << _name << " destroyed" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (_energyPoints <= 0) {
		std::cout << "ClapTrap " << _name << " has no energy to attack!" << std::endl;
		return;
	}
	if (_hitPoints <= 0) {
		std::cout << "ClapTrap " << _name << " is dead and cannot attack!" << std::endl;
		return;
	}
	
	std::cout << "ClapTrap " << _name << " attacks " << target
						<< ", causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
	_hitPoints -= amount;
	if (_hitPoints < 0)
		_hitPoints = 0;
	
	std::cout << "ClapTrap " << _name << " takes " << amount 
						<< " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (_energyPoints <= 0) {
		std::cout << "ClapTrap " << _name << " has no energy to repair!" << std::endl;
		return;
	}
	if (_hitPoints <= 0) {
		std::cout << "ClapTrap " << _name << " is dead and cannot repair!" << std::endl;
		return;
	}
	
	_hitPoints += amount;
	_energyPoints--;
	std::cout << "ClapTrap " << _name << " repairs itself for " << amount 
						<< " hit points!" << std::endl;
}
