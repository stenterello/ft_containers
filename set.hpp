/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/20 14:45:37 by ddelladi         ###   ########.fr       */
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
	class set
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
			typedef Node<value_type>										node_type;
			typedef RBTreeSet<key_type, node_type, key_compare>				tree_type;
			typedef typename ft::RBIterator<Key, Compare, node_type>		iterator;
			typedef typename ft::RBIterator<const Key, Compare, node_type>	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc()) :
				_alloc(alloc),
				_key_compare(comp),
				_value_compare(comp)
			{};
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = allocator_type()) :
				_alloc(alloc),
				_key_compare(comp),
				_value_compare(comp)
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
				this->_tree.clear();
				this->insert(rhs.begin(), rhs.end());
			};
			virtual ~set() { this->_tree.clear(); }

			allocator_type	get_allocator() const { return allocator_type(); };


			// Iterators

			iterator				begin() { return (this->_tree.begin()); };
			const_iterator			begin() const { return (this->_tree.begin()); };
			iterator				end() { return (this->_tree.end()); };
			const_iterator			end() const { return (this->_tree.end()); };
			reverse_iterator		rbegin() { return (--(this->_tree.end())); };
			const_reverse_iterator	rbegin() const { return (--(this->_tree.end())); };
			reverse_iterator		rend() { return (iterator(--(this->_tree.begin()))); };
			const_reverse_iterator	rend() const { return (iterator(--(this->_tree.begin()))); };


			// // Capacity

			bool		empty() const { return (this->_tree.size() > 0 ? false : true); };
			size_type	size() const { return (this->_tree.size()); };
			size_type	max_size() const { return (this->_tree.max_size()); };

			// Modifiers

			void						clear() { this->_tree.clear(); };
			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				return (this->_tree.insert(value));
			}
			iterator insert(iterator pos, const value_type& value)
			{
				(void)pos;
				return (this->_tree.insert(value).first);
			}
			template <class InputIt>
			void						insert(InputIt first, InputIt last)
			{
				while (first != last)
					this->_tree.insert(*first++);
			};
			// iterator					erase(iterator pos)
			// {};
			// size_type					erase(const Key& key);
			// void						swap(set& other) {};


			// // Lookup

			size_type		count(const Key& key) const { return (this->_tree.count()); };
			iterator		find(const Key& key) { return (this->_tree.find(key)); }
			const_iterator	find(const Key& key) const { return (this->_tree.const_find(key)); };
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
			tree_type		_tree;
	};
}
