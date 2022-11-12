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
	std::vector<int>	uno(10);
	std::vector<int>	due(20);
	uno.resize(10);
	due.resize(20);
	std::cout << uno.capacity() << std::endl;
	std::cout << due.capacity() << std::endl;
	std::swap(uno, due);
	std::cout << uno.capacity() << std::endl;
	std::cout << due.capacity() << std::endl;
	return (0);
}
