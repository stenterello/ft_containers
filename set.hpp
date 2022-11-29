/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/29 18:10:32 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include "utility.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set : public RBTreeSet<Key, Node<Key>, Compare, Alloc>
	{
		public:
			typedef Key														key_type;
			typedef Key														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_value_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
			};
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_value_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
				this->insert(first, last);
			};
			set(const set& other)
			{
				this->_key_type = other._key_type;
				this->_value_type = other._value_type;
				this->_key_compare = other._key_compare;
				this->_value_compare = other._value_compare;
				if (other.begin() != other.end())
					this->insert(other.begin(), other.end());
			};
			set&	operator=(const set& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_key_type = rhs._key_type;
				this->_value_type = rhs._value_type;
				this->_key_compare = rhs._key_compare;
				this->_value_compare = rhs._value_compare;
				this->_alloc = rhs._alloc;
				this->clear();
				this->insert(rhs.begin(), rhs.end());
				return (*this);
			};
			virtual ~set() { this->clear(); }
	};

	template <class T, class Compare, class Alloc>
	bool operator==(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		typename set<T, Compare, Alloc>::iterator	iter = lhs.begin();
		typename set<T, Compare, Alloc>::iterator	iter2 = rhs.begin();
	
		while (iter != lhs.end())
		{
			if (*iter != *iter2)
				return (0);
			iter++;
			iter2++;
		}
		if (iter2 != rhs.end())
			return (0);
		return (1);
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs < rhs));
	}
}
