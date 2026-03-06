#include "MutantStack.hpp"

template <typename T, typename C>
MutantStack<T, C>::MutantStack()
{
	std::cout << "Default constructor called!" << std::endl;
}

template <typename T, typename C>
MutantStack<T, C>::MutantStack(const MutantStack<T, C> &other) : std::stack<T, C>(other)
{
	std::cout << "Copy constructor called!" << std::endl;
}

template <typename T, typename C>
MutantStack<T, C> &MutantStack<T, C>::operator=(const MutantStack &other)
{
	std::cout << "Copy assignment operator called!" << std::endl;
	if (this != &other)
		std::stack<T, C>::operator=(other);
	return (*this);
}

template <typename T, typename C>
MutantStack<T, C>::~MutantStack()
{
	std::cout << "Destructor called!" << std::endl;
}

template <typename T, typename C>
typename MutantStack<T, C>::iterator MutantStack<T, C>::begin()
{
	return this->c.begin();
}

template <typename T, typename C>
typename MutantStack<T, C>::iterator MutantStack<T, C>::end()
{
	return this->c.end();
}

template <typename T, typename C>
typename MutantStack<T, C>::const_iterator MutantStack<T, C>::begin() const
{
	return this->c.begin();
}

template <typename T, typename C>
typename MutantStack<T, C>::const_iterator MutantStack<T, C>::end() const
{
	return this->c.end();
}

template <typename T, typename C>
typename MutantStack<T, C>::reverse_iterator MutantStack<T, C>::rbegin()
{
	return this->c.rbegin();
}

template <typename T, typename C>
typename MutantStack<T, C>::reverse_iterator MutantStack<T, C>::rend()
{
	return this->c.rend();
}

template <typename T, typename C>
typename MutantStack<T, C>::const_reverse_iterator MutantStack<T, C>::rbegin() const
{
	return this->c.rbegin();
}

template <typename T, typename C>
typename MutantStack<T, C>::const_reverse_iterator MutantStack<T, C>::rend() const
{
	return this->c.rend();
}
