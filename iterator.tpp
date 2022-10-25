/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:34:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/25 18:51:25 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"

template <class InputIterator>
InputIterator&	ft::operator++(void)
{
	return (InputIterator::pointer++);
}

template <class InputIterator, class Distance>
void	ft::iterator::advance(InputIterator & it, Distance n)
{
	for (Distance i = 0; i < n; i++)
		InputIterator++;
}

