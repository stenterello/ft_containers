#include <list>
#include "set.hpp"

#define T1 char
#define TESTED_NAMESPACE ft
#define _pair ft::pair
typedef TESTED_NAMESPACE::set<T1>::iterator ft_iterator;
typedef TESTED_NAMESPACE::set<T1>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T2>
void	printReverse(TESTED_NAMESPACE::set<T2> &st)
{
	typename TESTED_NAMESPACE::set<T2>::iterator it = st.end(), ite = st.begin();

	std::cout << "printReverse:" << std::endl;
	while (it-- != ite)
		std::cout << "-> " << printPair(it, false) << std::endl;
	std::cout << "_______________________________________________" << std::endl;
}


template <typename SET>
void	ft_bound(SET &st, const T1 &param)
{
	ft_iterator ite = st.end(), it[2];
	_pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
	ft_range = st.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename SET>
void	ft_const_bound(const SET &st, const T1 &param)
{
	ft_const_iterator ite = st.end(), it[2];
	_pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
	ft_range = st.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <class T>
void	is_empty(T const &st)
{
	std::cout << "is_empty: " << st.empty() << std::endl;
}

int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back('a' + i);

	TESTED_NAMESPACE::set<T1> st(lst.begin(), lst.end()), st2;
	TESTED_NAMESPACE::set<T1>::iterator it;

	lst.clear();
	is_empty(st);
	printSize(st);

	is_empty(st2);
	st2 = st;
	is_empty(st2);

	it = st.begin();
	for (unsigned long int i = 3; i < 6; ++i)
		st.insert(i * 7);

	printSize(st);
	printSize(st2);

	st2.clear();
	is_empty(st2);
	printSize(st2);
	return (0);
}
