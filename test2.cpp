#include <iostream>
#include "set.hpp"
#include <set>
#include <type_traits>

int main()
{
	ft::set<int>	ciao;

	ciao.insert(1);
	ciao.insert(2);
	ciao.insert(3);

	ft::set<int>	ciao2;


	// ft::set<int>::iterator	iter = ciao.begin();
	// ft::set<int>::iterator	iter2 = ciao2.begin();

	// std::cout << ciao.size() << std::endl;
	// while (iter != ciao.end())
	// 	std::cout << *iter++ << std::endl;
	// std::cout << std::endl;

	// std::cout << ciao2.size() << std::endl;
	// while (iter2 != ciao2.end())
	// 	std::cout << *iter2++ << std::endl;
	// std::cout << std::endl;

	// ciao.swap(ciao2);

	// std::swap(ciao2, ciao);

	// iter = ciao.begin();
	// iter2 = ciao2.begin();

	// std::cout << ciao.size() << std::endl;
	// while (iter != ciao.end())
	// 	std::cout << *iter++ << std::endl;
	// std::cout << std::endl;

	// std::cout << ciao2.size() << std::endl;
	// while (iter2 != ciao2.end())
	// 	std::cout << *iter2++ << std::endl;
	// std::cout << std::endl;

	return (0);
}
