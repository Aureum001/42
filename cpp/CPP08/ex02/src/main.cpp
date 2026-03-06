#include "MutantStack.hpp"
#include <list>
/*
int main()
{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
				std::cout << *it << std::endl;
				++it;
		}
		std::stack<int> s(mstack);
		return 0;
}*/

int main() {
	std::cout << "\n===== Test 1: Basic char stack =====" << std::endl;
	// Test 1: Basic char stack
  MutantStack<char> cstack;
  cstack.push('a');
  cstack.push('a');
  std::cout << cstack.top() << std::endl;
  std::cout << cstack.size() << std::endl;

	std::cout << "\n===== Test 2: Alphabet test =====" << std::endl;
	// Test 2: Alphabet test
  std::cout << "Alphabet test" << std::endl;
  MutantStack<char> dstack;
  for (char c = 'a'; c <= 'z'; c++)
	dstack.push(c);
  std::cout << "Size of dstack is " << dstack.size() << std::endl;
  std::cout << "Top of dstack is " << dstack.top() << std::endl;
  for (MutantStack<char>::iterator it = dstack.begin(); it != dstack.end();
	   ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 3: Int stack =====" << std::endl;
	// Test 3: Int stack
  MutantStack<int> istack;
  for (int i = 0; i < 10; ++i)
	istack.push(i * i);
  std::cout << "Int stack contents: ";
  for (MutantStack<int>::iterator it = istack.begin(); it != istack.end(); ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 4: String stack =====" << std::endl;
	// Test 4: String stack
  MutantStack<std::string> sstack;
  sstack.push("hello");
  sstack.push("world");
  sstack.push("!");
  std::cout << "String stack: ";
  for (MutantStack<std::string>::iterator it = sstack.begin();
	   it != sstack.end(); ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 5: Const iteration =====" << std::endl;
	// Test 5: Const iteration
  const MutantStack<int> constStack = istack;
  std::cout << "Const stack contents: ";
  for (MutantStack<int>::const_iterator it = constStack.begin();
	   it != constStack.end(); ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 6: Reverse iteration =====" << std::endl;
	// Test 6: Reverse iteration
  std::cout << "Reverse int stack: ";
  for (MutantStack<int>::reverse_iterator rit = istack.rbegin();
	   rit != istack.rend(); ++rit)
	std::cout << *rit << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 7: Copy and assignment =====" << std::endl;
	// Test 7: Copy and assignment
  MutantStack<int> copyStack(istack);
  MutantStack<int> assignStack;
  assignStack = istack;
  std::cout << "Copy stack: ";
  for (MutantStack<int>::iterator it = copyStack.begin(); it != copyStack.end();
	   ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;
  std::cout << "Assign stack: ";
  for (MutantStack<int>::iterator it = assignStack.begin();
	   it != assignStack.end(); ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 8: Custom container (vector) =====" << std::endl;
	// Test 8: Custom container (vector)
  typedef MutantStack<int, std::vector<int> > VecStack;
  VecStack vstack;
  for (int i = 0; i < 5; ++i)
	vstack.push(i);
  std::cout << "Vector-based stack: ";
  for (VecStack::iterator it = vstack.begin(); it != vstack.end(); ++it)
	std::cout << *it << ' ';
  std::cout << std::endl;

	std::cout << "\n===== Test 9: Compare with std::list =====" << std::endl;
	// Test 9: Compare with std::list
	std::list<int> l;
	for (int i = 0; i < 10; ++i)
	  l.push_back(i * i);
	std::cout << "List contents: ";
	for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
	  std::cout << *it << ' ';
	std::cout << std::endl;
	std::cout << "List reverse: ";
	for (std::list<int>::reverse_iterator rit = l.rbegin(); rit != l.rend(); ++rit)
	  std::cout << *rit << ' ';
	std::cout << std::endl;

	// Compare with MutantStack
	MutantStack<int> mliststack;
	for (int i = 0; i < 10; ++i)
	  mliststack.push(i * i);
	std::cout << "MutantStack contents: ";
	for (MutantStack<int>::iterator it = mliststack.begin(); it != mliststack.end(); ++it)
	  std::cout << *it << ' ';
	std::cout << std::endl;
	std::cout << "MutantStack reverse: ";
	for (MutantStack<int>::reverse_iterator rit = mliststack.rbegin(); rit != mliststack.rend(); ++rit)
	  std::cout << *rit << ' ';
	std::cout << std::endl;

  return 0;
}
