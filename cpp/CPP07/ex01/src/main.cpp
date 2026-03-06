#include "iter.hpp"
#include <iostream>
#include <string>

void ft_printc(char c) { std::cout << c << std::endl; }
void ft_printi(int x) { std::cout << x << std::endl; }
void ft_printd(double x) { std::cout << x << std::endl; }
void ft_prints(std::string s) { std::cout << s << std::endl; }
void ft_printci(const int &x) { std::cout << x << std::endl; }

int main()
{
	std::string str = "hello world";
	char *copy = (char *)str.c_str();
	std::cout << "Test 1: char array from string" << std::endl;
	::iter<char>(&copy[0], str.size(), ft_printc);

	int intArr[] = {1, 2, 3, 4, 5};
	std::cout << "Test 2: int array" << std::endl;
	::iter<int>(intArr, 5, ft_printi);

	double dblArr[] = {3.14, 2.71, 1.41};
	std::cout << "Test 3: double array" << std::endl;
	::iter<double>(dblArr, 3, ft_printd);

	std::string sArr[] = {"foo", "bar", "baz"};
	std::cout << "Test 4: std::string array" << std::endl;
	::iter<std::string>(sArr, 3, ft_prints);

	const int constArr[] = {42, 43, 44};
	std::cout << "Test 5: const int array" << std::endl;
	::iter<const int>(constArr, 3, ft_printci);

	return 0;
}