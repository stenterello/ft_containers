#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	std::set<int, std::greater<int> >	ciao;

	ciao.insert(10);

	return (0);
}
