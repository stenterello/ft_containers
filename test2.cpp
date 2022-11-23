#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	std::set<int>	ciao;

	ciao.insert(16);
	ciao.insert(8);
	ciao.insert(23);
	ciao.insert(7);
	ciao.insert(19);
	ciao.insert(29);
	ciao.insert(41);
	ciao.insert(4);
	ciao.insert(11);
	
	std::set<int>::iterator	iter = ciao.find(16);
	iter = ciao.erase(iter);

	std::cout << *iter << std::endl;

	return (0);
}
