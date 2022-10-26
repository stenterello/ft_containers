/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:34:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/26 17:36:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class InputIterator, class Distance>
void	ft::advance(InputIterator & it, Distance n)
{
	for (Distance i = 0; i < n; i++)
		InputIterator++;
}
