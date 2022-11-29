/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/29 17:11:15 by ddelladi         ###   ########.fr       */
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
			typedef Alloc													allocator_type;			

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc()) :
				_key_compare(comp),
				_value_compare(comp),
				_key_type(key_type()),
				_value_type(value_type())
			{};
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = allocator_type()) :
				_key_compare(comp),
				_value_compare(comp),
				_key_type(key_type()),
				_value_type(value_type())
			{
				this->insert(first, last);
			};
			set(const set& other) :
				_key_type(other._key_type),
				_value_type(other._value_type),
				_key_compare(other._key_compare),
				_value_compare(other._value_compare)
			{
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

			allocator_type	get_allocator() const { return allocator_type(); }
			key_compare		key_comp() const { return (this->_key_compare); }
			value_compare	value_comp() const { return (this->_value_compare); }

		private:
			key_type		_key_type;
			value_type		_value_type;
			key_compare		_key_compare;
			value_compare	_value_compare;
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
