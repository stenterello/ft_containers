/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/29 01:21:05 by ddelladi         ###   ########.fr       */
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
	class set : public RBTreeSet<Key, Node<Key>, Compare>
	{
		public:
			typedef Key														key_type;
			typedef Key														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::RBIterator<Key, Compare, Node<Key> >		iterator;
			typedef typename ft::RBIterator<const Key, Compare, Node<Key> >	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc()) :
				_alloc(alloc),
				_key_compare(comp),
				_value_compare(comp),
				_key_type(key_type()),
				_value_type(value_type())
			{};
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = allocator_type()) :
				_alloc(alloc),
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
				_value_compare(other._value_compare),
				_alloc(other._alloc)
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
			allocator_type	_alloc;
	};
}
