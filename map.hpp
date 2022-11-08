/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:17:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/08 16:30:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "pair.hpp"
#include "iterator.hpp"
#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const Key, T>										value_type;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef ft::iterator<bidirectional_iterator_tag, value_type>		iterator;
			typedef const ft::iterator<bidirectional_iterator_tag, value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			class value_compare
			{};
			
			map() {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) {};
			template <class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {};
			map(const map& other) {};
			map&	operator=(const map& other) {};
			virtual ~map();
			allocator_type	get_allocator() const {};

			
			// Element access

			T&			at(const Key& key) {};
			const T&	at(const Key& key) const {};
			T&			operator[](const Key& key) {};


			// Iterators

			iterator				begin() {};
			const_iterator			begin() const {};
			iterator				end() {};
			const_iterator			end() const {};
			reverse_iterator		rbegin() {};
			const_reverse_iterator	rbegin() const {};
			reverse_iterator		rend() {};
			const_reverse_iterator	rend() const {};

			
			// Capacity

			bool		empty() const { return false; }; // Temporary
			size_type	size() const { return 0; }; // Temporary
			size_type	max_size() const { return 0; }; // Temporary


			// Modifiers

			void						clear() {};
			ft::pair<iterator, bool>	insert(const value_type& value) {};
			iterator					insert(iterator pos, const value_type& value) {};
			template <class InputIt>
			void						insert(InputIt first, InputIt last) {};
			iterator					erase(iterator pos) {};
			iterator					erase(iterator first, iterator last) {};
			size_type					erase(const Key& key) { return 0; }; // Temporary
			void						swap(map& other) {};


			// Lookup

			size_type								count(const Key& key) const { return 0; }; // Temporary
			iterator								find(const Key& key) {};
			const_iterator							find(const Key& key) const {};
			ft::pair<iterator,iterator>				equal_range(const Key& key) {};
			ft::pair<const_iterator,const_iterator>	equal_range(const Key& key) const {};
			iterator								lower_bound(const Key& key) {};
			const_iterator							lower_bound(const Key& key) const {};
			iterator								upper_bound(const Key& key) {};
			const_iterator							upper_bound(const Key& key) const {};


			// Observers

			key_compare		key_comp() const {};
			value_compare	value_comp() const {};
		private:
		
	};

	// bool	operator==(map const & lsh, map const & rhs) {};
	// bool	operator!=(map const & lsh, map const & rhs) {};
	// bool	operator<(map const & lsh, map const & rhs) {};
	// bool	operator<=(map const & lsh, map const & rhs) {};
	// bool	operator>(map const & lsh, map const & rhs) {};
	// bool	operator>=(map const & lsh, map const & rhs) {};

	// template< class Key, class T, class Compare, class Alloc >
	// void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) {};
	
}
