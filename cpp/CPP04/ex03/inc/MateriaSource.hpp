#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

#define SLOTS 4

class IMateriaSource;

class MateriaSource : public IMateriaSource {
private:
	AMateria *learntMaterias_[SLOTS];

public:
	MateriaSource();
	MateriaSource(const MateriaSource &other);
	MateriaSource &operator=(const MateriaSource &other);
	~MateriaSource();
	void learnMateria(AMateria *materiaToLearn);
	AMateria *createMateria(std::string const &type);
};

#endif