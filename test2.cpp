#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	std::set<int>	ciao;

	ciao.insert(1);
	ciao.insert(0);
	ciao.insert(3);
	ciao.insert(2);
	ciao.insert(5);
	ciao.insert(4);
	ciao.insert(7);
	ciao.insert(6);
	ciao.insert(9);
	ciao.insert(8);

	std::set<int>::iterator	iter = ciao.begin();

	while (iter != ciao.end())
		std::cout << *(++iter) << std::endl;

	std::cout << std::endl;

	std::cout << ciao.begin() + 1 << std::endl;
	return (0);
}
