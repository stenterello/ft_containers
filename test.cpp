/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:37 by gimartin          #+#    #+#             */
/*   Updated: 2022/11/03 16:58:28 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "vector.hpp"
#include <vector>
#include <iterator>

int	main()
{
	// std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<int>		hello(5, 5);
	hello.reserve(10);
	hello.assign(2, 3);
	hello.push_back(5);
	hello.push_back(7);
	hello.erase(hello.begin() + 2);
	// ft::vector<int>		hello2(hello);
	// ft::vector<std::string>	hello3;
	// hello3.resize(10, "test");
	// hello3.assign(test, test + 4);
	
	std::vector<int>	ciao(5, 5);
	ciao.reserve(10);
	ciao.assign(2, 3);
	ciao.push_back(5);
	ciao.push_back(7);
	ciao.erase(ciao.begin() + 2);
	// std::vector<int>	ciao2(ciao);
	// std::vector<std::string>	ciao3;
	// ciao3.resize(10, "test");
	// ciao3.assign(test, test + 4);


	// int test[] = { 1, 2, 3 };
	// ft::vector<int> v1;
	// std::vector<int> v2;
	// v1.insert(v1.begin(), test, test + 3);
	// v1.insert(v1.begin(), 42);
	// v1.insert(v1.end(), 21);
	// v1.insert(v1.begin(), 10);
	// v1.insert(v1.begin() + 1, 11);
	// v1.insert(v1.begin() + 2, (size_t)3, 0);
	// v1.insert(v1.begin() + 1, test, test + 3);
	// v2.insert(v2.begin(), test, test + 3);
	// v2.insert(v2.begin(), 42);
	// v2.insert(v2.end(), 21);
	// v2.insert(v2.begin(), 10);
	// v2.insert(v2.begin() + 1, 11);
	// v2.insert(v2.begin() + 2, (size_t)3, 0);
	// v2.insert(v2.begin() + 1, test, test + 3);

	std::cout << "FT" << std::endl;

	ft::vector<int>::iterator	iter;

	iter = hello.begin();
	while (iter != hello.end())
	{
		std::cout << *iter << std::endl;
		iter++;
	}
	std::cout << "FT size: " << hello.size() << std::endl;
	std::cout << "FT capacity: " << hello.capacity() << std::endl;

	std::cout << "STD" << std::endl;


	std::vector<int>::iterator	iter2;

	iter2 = ciao.begin();
	while (iter2 != ciao.end())
	{
		std::cout << *iter2 << std::endl;
		iter2++;
	}
	std::cout << "STD size: " << ciao.size() << std::endl;
	std::cout << "STD capacity: " << ciao.capacity() << std::endl;

	std::vector<int>	empty;

	empty.reserve(1);
	std::cout << &(*empty.begin()) << std::endl;
	std::cout << &(*empty.end()) << std::endl;
	return (0);
}
