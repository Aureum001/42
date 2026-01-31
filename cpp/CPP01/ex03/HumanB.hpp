#ifndef EX03_HUMANB_HPP
#define EX03_HUMANB_HPP

#include "Weapon.hpp"

class HumanB {
private:
	Weapon *_weapon;
	std::string _name;
public:
	explicit HumanB(const std::string& name);

	void setWeapon(Weapon& weapon);

	void attack() const;
};


#endif
