#include "iterator.hpp"
#include "rb_tree.hpp"
#include <iostream>

int	main()
{
	ft::RBTreeSet<int, ft::Node<int> >				ciao;
	ft::RBTreeSet<int, ft::Node<int> >::iterator	iter;

	ciao.insert(6);
	ciao.insert(2);
	ciao.insert(1);
	ciao.insert(8);
	ciao.insert(4);
	ciao.insert(3);
	ciao.insert(12);
	ciao.insert(9);
	ciao.insert(15);
	ciao.insert(27);
	ciao.insert(48);
	ciao.insert(42);
	ciao.insert(35);
	ciao.insert(5);
	ciao.insert(22);
	ciao.insert(6);
	ciao.insert(7);
	iter = ciao.find(3);
	if (iter.node)
		std::cout << *iter << std::endl;
	std::cout << ciao.count(ciao.begin()) << std::endl;
	std::cout << (ciao.min()->data) << std::endl;
	std::cout << (ciao.max()->data) << std::endl;
	std::cout << ciao.getPredecessor(iter.node)->data << std::endl;
	std::cout << "count before " << ciao.count() << std::endl;
	ciao.erase(1);
	std::cout << "count after " << ciao.count() << std::endl;

	return (0);
}
