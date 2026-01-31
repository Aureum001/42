#ifndef EX03_WEAPON_HPP
#define EX03_WEAPON_HPP

#include <string>
#include <iostream>

class Weapon {
private:
	std::string type;
public:
	Weapon(const std::string& typeName);

	const std::string& getType() const;
	void setType(const std::string& typeName);
};

#endif