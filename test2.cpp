#include <list>
#include <iostream>
#include <set>

#define T1 int
#define TESTED_NAMESPACE std
#define _pair std::pair
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

template <typename SET, typename U>
void	ft_erase(SET &st, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	st.erase(param);
	printSize(st);
}

template <typename SET, typename U, typename V>
void	ft_erase(SET &st, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	st.erase(param, param2);
	printSize(st);
}


int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i);
	TESTED_NAMESPACE::set<T1> st(lst.begin(), lst.end());
	printSize(st);

	for (int i = 2; i < 4; ++i)
		ft_erase(st, i);

	ft_erase(st, *st.begin());
	ft_erase(st, *(--st.end()));

	st.insert(-1);
	st.insert(10);
	st.insert(10);
	printSize(st);

	ft_erase(st, 0);
	ft_erase(st, 1);
	printSize(st);

	return (0);
}
