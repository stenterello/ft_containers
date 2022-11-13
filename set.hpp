/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/13 13:13:45 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include "iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
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
		typedef typename ft::bidirectional_iterator<Key>				iterator;
		typedef typename ft::bidirectional_iterator<const Key>			const_iterator;
		typedef	typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

		public:
			set() : _size(0), _begin(NULL), _end(NULL) {};
			// explicit set(const Compare& comp, const Allocator& alloc = Allocator()) {};
			// template <class InputIt>
			// set(InputIt first, InputIt last, const Allocator& alloc) : set(first, last, Compare(), alloc) {};
			set(const set& other) :
			_key_type(other._key_type),
			_value_type(other._value_type),
			_key_compare(other._key_compare),
			_value_compare(other._value_compare),
			_size(other.size),
			_alloc(other._alloc),
			{
				// Copia il contenuto
			};
			set&	operator=(const set& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_key_type = rhs._key_type;
				this->_value_type = rhs._value_type;
				this->_key_compare = rhs._key_compare;
				this->_value_compare = rhs._value_compare;
				this->_size = rhs._size;
				this->_alloc = rhs._alloc;
				// Copia il contenuto
			};
			virtual ~set() {};

			allocator_type	get_allocator() const { return allocator_type(); };


			// // Iterators

			// iterator				begin() {};
			// const_iterator			begin() const {};
			// iterator				end() {};
			// const_iterator			end() const {};
			// reverse_iterator		rbegin() {};
			// const_reverse_iterator	rbegin() const {};
			// reverse_iterator		rend() {};
			// const_reverse_iterator	rend() const {};


			// // Capacity

			bool		empty() const { return (_size > 0 ? false : true); };
			size_type	size() const { return (this->_size); };
			size_type	max_size() const { return (allocator_type().max_size()); };


			// // Modifiers

			// void						clear() {};
			// ft::pair<iterator, bool>	insert(value_type&& value) {};
			// template <class InputIt>
			// void						insert(InputIt first, InputIt last) {};
			// iterator					erase(iterator pos) {};
			// size_type					erase(const Key& key);
			// void						swap(set& other) {};


			// // Lookup

			// size_type	count(const Key& key) const {};
			// iterator	find(const Key& key);
			// const_iterator	find(const Key& key) const {};
			// ft::pair<iterator, iterator>	equal_range(const Key& key) {};
			// ft::pair<const_iterator,m const_iterator>	equal_range(const Key& key) const {};
			// iterator									lower_bounf(const Key& key) {};
			// const_iterator								lower_bound(const Key& key) const {};
			// iterator									upper_bound(const Key& key) {};
			// const_iterator								upper_bound(const Key& key) const {};

			
			// // Observers

			// key_compare		key_comp() const {};
			// value_compare	value_comp() const {};

		private:
			key_type		_key_type;
			value_type		_value_type;
			key_compare		_key_compare;
			value_compare	_value_compare;
			allocator_type	_alloc;
			size_type		_size;
			pointer			_begin;
			pointer			_end;
	};
}
