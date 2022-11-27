#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	std::set<int>	uno;
	std::set<int>	due;

	uno.insert(1);
	uno.insert(2);
	uno.insert(3);
	due.insert(4);
	due.insert(5);
	due.insert(6);

	uno.swap(due);

	return (0);
}
