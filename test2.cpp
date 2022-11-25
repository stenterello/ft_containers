#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	ft::set<int, std::greater<int> > st;
	ft::set<int, std::greater<int> > st2;
    st.insert(10);
    st2.insert(10);
	if (st.lower_bound(11) == st.end())
		std::cout << "CUIAO1" << std::endl;
	if (st2.lower_bound(11) == st2.end())
		std::cout << "CIAO2" << std::endl;
	std::cout << *(st.lower_bound(11)) << std::endl;
	std::cout << *(st2.lower_bound(11)) << std::endl;

	return (0);
}
