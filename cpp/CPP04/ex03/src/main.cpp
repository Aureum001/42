#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int main() {
	std::cout << "=== Subject Test ===" << std::endl;
	{
		IMateriaSource *src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter *me = new Character("me");
		AMateria *tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter *bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		delete bob;
		delete me;
		delete src;
	}

	std::cout << "\n=== Deep Copy Test ===" << std::endl;
	{
		Character *original = new Character("original");
		original->equip(new Ice());
		original->equip(new Cure());
		
		Character *copy = new Character(*original);
		std::cout << "\nUsing original:" << std::endl;
		original->use(0, *original);
		std::cout << "Using copy:" << std::endl;
		copy->use(0, *copy);
		
		delete original;
		std::cout << "\nOriginal deleted, copy still works:" << std::endl;
		copy->use(1, *copy);
		delete copy;
	}

	std::cout << "\n=== Unequip Test ===" << std::endl;
	{
		Character hero("hero");
		AMateria *ice = new Ice();
		AMateria *cure = new Cure();
		
		hero.equip(ice);
		hero.equip(cure);
		hero.use(0, hero);
		hero.use(1, hero);
		
		std::cout << "Unequipping ice..." << std::endl;
		hero.unequip(0);
		hero.use(0, hero);
		
		std::cout << "Ice will be deleted by Character destructor" << std::endl;
	}

	std::cout << "\n=== Full Inventory Test ===" << std::endl;
	{
		Character warrior("warrior");
		AMateria *extra = new Ice();
		
		warrior.equip(new Ice());
		warrior.equip(new Cure());
		warrior.equip(new Ice());
		warrior.equip(new Cure());
		warrior.equip(extra);
		
		delete extra;
	}

	std::cout << "\n=== Unknown Materia Type Test ===" << std::endl;
	{
		IMateriaSource *src = new MateriaSource();
		src->learnMateria(new Ice());
		
		AMateria *unknown = src->createMateria("fire");
		if (unknown == NULL)
			std::cout << "Unknown type correctly returns NULL" << std::endl;
		
		delete src;
	}

	return 0;
}
