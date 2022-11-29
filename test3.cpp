#include <iostream>

#include <map>

int	main()
{
	std::map<int, int>	mappa;
	std::pair<int, int>	p(1, 2);

	mappa.insert(p);

	std::cout << mappa.find(2)->first << std::endl;
	return (0);
}