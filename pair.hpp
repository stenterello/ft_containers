/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:02:40 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/08 15:15:53 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		first_type	first;
		second_type	second;
		pair() : first(), second() {}
		pair(const T1 & x, const T2 & y) : first(x), second(y) {}
		template <class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
		pair&	operator=(pair const & rhs)
		{
			if (this == &rhs)
				return (*this);
			first = rhs.first;
			second = rhs.second;
			return (*this);
		}
		virtual ~pair() {};
	};

	template <class T1, class T2>
	bool	operator==(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first != rhs.first || lhs.second != rhs.second) return (false);
		return (true); 
	};

	// template <class T1, class T2, class T3, class T4>
	// bool	operator==(pair<T1, T2> const & lhs, pair<T3, T4> const & rhs)
	// {
	// 	if (lhs.first != rhs.first || lhs.second != rhs.second) return (false);
	// 	return (true); 
	// };

	template <class T1, class T2>
	bool	operator!=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first != rhs.first || lhs.second != rhs.second) return (true);
		return (false); 
	};

	template <class T1, class T2>
	bool	operator<(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first >= rhs.first || lhs.second >= rhs.second) return (false);
		return (true); 
	};

	template <class T1, class T2>
	bool	operator<=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first > rhs.first || lhs.second > rhs.second) return (false);
		return (true); 
	};

	template <class T1, class T2>
	bool	operator>(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first <= rhs.first || lhs.second <= rhs.second) return (false);
		return (true); 
	};

	template <class T1, class T2>
	bool	operator>=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		if (lhs.first < rhs.first || lhs.second < rhs.second) return (false);
		return (true); 
	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}
}
