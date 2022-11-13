#include "set.hpp"
#include <iostream>

int	main()
{
	ft::set<int>	ciao;
	// std::cout << "allocator_type: " << ciao.get_allocator() << std::endl;
	std::cout << "max size: " << ciao.max_size() << std::endl;
	std::cout << "empty: " << ciao.empty() << std::endl;
	std::cout << "size: " << ciao.size() << std::endl;
	return (0);
}
