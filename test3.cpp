#include <iostream>

#include "map.hpp"
#include <map>


int	main()
{
	ft::map<std::string, std::string>	ciao;
	ft::map<std::string, std::string>	ciao2;

	ciao.insert(ft::make_pair("123", "124"));
	// ciao.insert(ft::make_pair(2, 3));
	ciao2.insert(ft::make_pair("124", "123"));

	 ciao.value_comp();
	
	return (0);
}
