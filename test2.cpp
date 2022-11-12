#include "utility.hpp"
#include "vector.hpp"
#include "iterator.hpp"
#include <iostream>

int	main()
{
	ft::vector<int>	uno(10);
	ft::vector<int>::iterator	iter1 = uno.begin();
	ft::vector<int>::iterator	iter2 = uno.end();

	std::cout << ft::distance(iter2, iter1) << std::endl;
	return (0);
}

