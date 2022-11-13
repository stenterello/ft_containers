#include <iostream>
#include <iterator>
#include <set>

int main()
{
	std::set<int>			ciao;
	std::cout << *ciao.begin() << std::endl;
	// std::set<int>::iterator	iter = ciao.begin();

	// while (iter != ciao.end())
	// 	std::cout << *iter++ << std::endl;
	return (0);
}
