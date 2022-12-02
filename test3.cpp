#include <iostream>
#include "set.hpp"

	template <typename T>
	struct Node
	{
		int	color;
		Node		*parent;
		Node		*child[2];
		T 			data;

		template <class U, class V>
		Node(std::pair<U, V> const & val) : data(val) {};
	};

int main()
{
	ft::set<int>			ciao;


	std::cout << ciao.max_size() << std::endl;

	return (0);
}