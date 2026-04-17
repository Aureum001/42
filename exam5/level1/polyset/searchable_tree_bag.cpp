#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag(){}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &source) : tree_bag(source){}
searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &source)
{
	if (this != &source)
		tree_bag::operator=(source);
	return (*this);
}
searchable_tree_bag::~searchable_tree_bag(){}
bool searchable_tree_bag::has(int value) const
{
	node* current = this->tree;
	while (current != nullptr) {
		if (current->value == value)
			return true;
		else if (value < current->value)
			current = current->l;
		else
			current = current->r;
	}
	return false;
}
