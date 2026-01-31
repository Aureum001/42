#include "Weapon.hpp"

Weapon::Weapon(const std::string& typeName) : type(typeName) {
}

const std::string& Weapon::getType() const {
	return (type);
}

void Weapon::setType(const std::string& typeName) {
	type = typeName;
}