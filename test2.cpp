#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	ft::set<int>	ciao;
	ft::set<int>	ciao2;

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

	for (ft::set<int>::iterator it = ciao.begin(); it != ciao.end(); it++)
	{ ciao2.insert(*it); }


	return (0);
}
