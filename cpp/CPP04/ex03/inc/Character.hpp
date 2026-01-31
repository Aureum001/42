#ifndef EX03_CHARACTER_HPP
#define EX03_CHARACTER_HPP

#include "ICharacter.hpp"
#include <list>

#define SLOTS 4

class ICharacter;
class AMateria;

class Character : public ICharacter {
private:
	std::string name_;
	AMateria *inventory_[SLOTS];
	std::list<AMateria *> unequipedMaterias_;

public:
	Character(std::string const &name);
	Character(const Character &other);
	Character &operator=(const Character &other);
	~Character();
	const std::string &getName() const;
	void equip(AMateria *m);
	void unequip(int idx);
	void use(int idx, ICharacter &target);
};

#endif