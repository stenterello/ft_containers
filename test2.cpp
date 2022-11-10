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
	std::vector<int>	ciao;

	ciao.reserve(15);
	std::cout << ft::distance(ciao.begin(), ciao.end()) << std::endl;
	return (0);
}