/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:37 by gimartin          #+#    #+#             */
/*   Updated: 2022/11/07 20:19:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iterator>
#include <iostream>

int	main()
{
	std::vector<int> 					ciao = { 1, 2, 3, 4, 5 };
	std::vector<int>::iterator			iter = ciao.begin();
	std::vector<int>::reverse_iterator	iter2(iter);

	std::cout << *(iter2 - 1) << std::endl;
	return (0);
}
