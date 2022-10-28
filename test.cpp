/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:37 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/28 17:45:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "vector.hpp"
// #include <vector>
// #include <iterator>

int	main()
{
	ft::vector<int>	hello(5, 5);
	std::cout << hello.size() << std::endl;
	std::cout << hello.empty() << std::endl;
	std::cout << hello.capacity() << std::endl;
	hello.reserve(10);
	std::cout << hello.capacity() << std::endl;
	hello.assign(2, 3);
	ft::vector<int>::iterator	it;
	it = hello.begin();


	// std::vector<int>			prova(10, 10);
	// std::vector<int>::iterator	iter;
	// iter = prova.begin();
	// while (iter != prova.end())
	// {
	// 	std::cout << *iter << std::endl;
	// 	iter++;
	// }
	// std::cout << "Capacity: " << prova.capacity() << std::endl;
	// std::cout << "Size: " << prova.size() << std::endl;
	// prova.assign(5, 5);
	// iter = prova.begin();
	// while (iter != prova.end())
	// {
	// 	std::cout << *iter << std::endl;
	// 	iter++;
	// }
	// std::cout << "Capacity: " << prova.capacity() << std::endl;
	// std::cout << "Size: " << prova.size() << std::endl;
	return (0);
}