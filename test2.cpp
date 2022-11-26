#include <iostream>
#include "set.hpp"
#include <set>

int main()
{
	ft::set<int, std::greater<int> > st;
    st.insert(10);
    st.insert(11);
	st.insert(9);
	ft::pair<ft::set<int, std::greater<int> >::iterator, ft::set<int, std::greater<int> >::iterator>	p;

	p = ft::make_pair(st.lower_bound(10), st.upper_bound(10));

	std::cout << *(p.first) << " " << *(p.second) << std::endl;

	return (0);
}
