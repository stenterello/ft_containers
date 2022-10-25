/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:34:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/25 20:14:51 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"

template <class InputIterator>
InputIterator&	ft::operator++()
{
	return (InputIterator::pointer++);
}

template <class InputIterator, class Distance>
void	ft::advance(InputIterator & it, Distance n)
{
	for (Distance i = 0; i < n; i++)
		InputIterator++;
}

