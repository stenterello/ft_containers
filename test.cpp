/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:37 by gimartin          #+#    #+#             */
/*   Updated: 2022/11/02 19:06:39 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "vector.hpp"
#include <vector>
#include <iterator>

int	main()
{
	ft::vector<int>		hello(5, 5);
	hello.reserve(10);
	hello.assign(2, 3);
	hello.push_back(5);
	ft::vector<int>		hello2(hello);
	
	std::vector<int>	ciao(5, 5);
	ciao.reserve(10);
	ciao.assign(2, 3);
	ciao.push_back(5);
	std::vector<int>	ciao2(ciao);

	std::cout << "FT" << std::endl;

	ft::vector<int>::iterator	iter;

	iter = hello2.begin();
	while (iter != hello2.end())
	{
		std::cout << *iter << std::endl;
		iter++;
	}

	std::cout << "STD" << std::endl;


	std::vector<int>::iterator	iter2;

	iter2 = ciao2.begin();
	while (iter2 != ciao2.end())
	{
		std::cout << *iter2 << std::endl;
		iter2++;
	}

	std::vector<int>	empty;

	empty.reserve(1);
	std::cout << &(*empty.begin()) << std::endl;
	std::cout << &(*empty.end()) << std::endl;
	return (0);
}
