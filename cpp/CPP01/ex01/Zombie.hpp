#ifndef EX01_ZOMBIE_HPP
#define EX01_ZOMBIE_HPP

#include <iostream>

class Zombie {
private:
	std::string name;
public:
	Zombie();
	
	void announce();
	void setName(const std::string& inputName);
	
	~Zombie();
};

Zombie *zombieHorde(int N, const std::string& name);


#endif
