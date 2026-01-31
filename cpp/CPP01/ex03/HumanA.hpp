#ifndef EX03_HUMANA_HPP
#define EX03_HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
private:
	Weapon &_weapon;
	std::string _name;

public:
	HumanA(const std::string& name, Weapon& weapon);

	void attack() const;
};


#endif
