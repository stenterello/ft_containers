#include <iostream>
#include <iterator>
#include <set>

int main()
{
	std::set<int>			ciao = { 0, 5, 6, 4, 2, 1, 8 };
	
	
	std::cout << (ciao.insert(3)) << std::endl;
	// std::set<int>::iterator	iter = ciao.begin();

	// while (iter != ciao.end())
	// 	std::cout << *iter++ << std::endl;
	return (0);
}
