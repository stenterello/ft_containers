#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	ft::set<int>	ciao;

	ciao.insert(16);
	ciao.insert(8);
	ciao.insert(23);
	ciao.insert(7);
	ciao.insert(19);
	ciao.insert(29);
	ciao.insert(41);
	ciao.insert(4);
	ciao.insert(11);

	std::cout << *(ciao.lower_bound(6)) << std::endl;

	return (0);
}
