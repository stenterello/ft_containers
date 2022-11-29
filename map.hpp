/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:17:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/29 18:19:44 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "utility.hpp"
#include "rb_tree.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map : public RBTreeSet<ft::pair<Key, T>, Node<ft::pair<Key, T> >, Compare, Allocator>
	{
		public:
			typedef Key														key_type;
			typedef	T														mapped_type;
			typedef ft::pair<Key, T>										value_type;

			map() {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) {};
			template <class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {};
			map(const map& other) {};
			~map() {};
	};
}
