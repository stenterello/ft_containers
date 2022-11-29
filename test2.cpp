#include <iostream>
#include "set.hpp"
#include <set>
#include <type_traits>

int main()
{
	std::set<int>	ciao;
	std::set<int>	ciao2;

	ciao.insert(1);
	// ciao2.insert(2);

	std::cout << std::boolalpha << (ciao < ciao2) << std::endl;

	return (0);
}
