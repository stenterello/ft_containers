#include "iterator.hpp"
#include "vector.hpp"
#include <vector>
#include <iterator>
#include <list>

ft::vector<int>	test()
{
	ft::vector<int>	ciao(4, 4);

	ciao.resize(2);
	return (ciao);
}



int	main()
{
	ft::vector<int>	ciao(15, 5);
	ciao.insert(ciao.begin() + 3, 5, 7);
	ft::vector<int>::iterator	iter = ciao.begin();
	while (iter != ciao.end())
		std::cout << *iter++ << std::endl;
	std::cout << std::endl;
	std::vector<int>	ciao2(15, 5);
	ciao2.insert(ciao2.begin() + 3, 5, 7);
	std::vector<int>::iterator	iter2 = ciao2.begin();
	while (iter2 != ciao2.end())
		std::cout << *iter2++ << std::endl;	
	return (0);
}