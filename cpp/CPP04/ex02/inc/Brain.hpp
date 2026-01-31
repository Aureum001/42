#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>
#include <cstdlib>

#define IDEAS 100

class Brain {
private:
	std::string ideas[IDEAS];

public:
	Brain();
	Brain(const Brain &other);
	Brain &operator=(const Brain &other);
	~Brain();
	void RandomIdeas();
};

#endif