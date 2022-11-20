#include <iostream>
#include <iterator>
#include <set>

int main()
{
	std::set<int>			ciao = { 7, 5, 6, 4, 2, 1, 8 };
	
	
	std::cout << *(ciao.begin()) << std::endl;	// 	std::cout << *iter++ << std::endl;
	return (0);
}
