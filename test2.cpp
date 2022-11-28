#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	ft::set<int, std::plus<int> >	ciao;

	ciao.insert(16);
	ciao.insert(8);
	ciao.insert(23);
	ciao.insert(7);
	ciao.insert(19);
	ciao.insert(29);
	ciao.insert(41);
	ciao.insert(4);
	ciao.insert(11);

	ft::set<int, std::plus<int> >::iterator	begin = ciao.begin();
	ft::set<int, std::plus<int> >::iterator	end = ciao.end();
	for (ft::set<int, std::plus<int> >::iterator	iter = ciao.begin(); iter != ciao.end(); iter++)
		std::cout << *iter << std::endl;

	// std::plus<int>	p;

	// std::cout << "PLUS: " <<  p(1, 1) << std::endl;

	// std::minus<int>	m;

	// std::cout << "MINUS: " << m(1, 1) << std::endl;

	// std::greater<int>	g;

	// std::cout << "GREATER: " << g(1, 1) << std::endl;

	// std::less<int>	l;

	// std::cout << "LESS: " << l(1, 1) << std::endl;

	return (0);
}
