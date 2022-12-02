#include "set.hpp"
#include <iostream>

int main()
{
	ft::set<int>	ciao;

	ciao.insert(1);
	ciao.insert(2);
	ciao.insert(3);
	ciao.insert(4);
	ciao.insert(5);
	ciao.insert(6);
	ciao.insert(7);
	ciao.insert(8);
	ciao.insert(9);
	ciao.insert(10);

	ciao.erase(2);
	ciao.erase(1);
	ciao.erase(10);
	ciao.erase(3);
	ciao.erase(4);
	ciao.erase(5);
	ciao.erase(7);
	ciao.erase(8);

	return (0);
}
