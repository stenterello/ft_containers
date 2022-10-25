/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:28:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/25 18:47:10 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
			size_type											_size;
			size_type											_capacity;
			pointer												_begin;
			pointer												_end;
			allocator_type										_alloc;
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			//iterator
			//const_iterator
			//reverse_iterator
			//const_reverse_iterator

			//Constructor

			explicit vector (const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_alloc(alloc),
			{}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_alloc(alloc),
			{
				if (n > 0)
				{
					_size = n;
					_capacity = 1;
					while (_capacity < n)
						_capacity *= 2;
					_begin = _alloc.allocate(_capacity);
					for (size_t i = 0; i < n; i++)
						_begin[i] = val;
				}
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_alloc(alloc),
			{
				assign(first, last);
			}

			vector (const vector& x):
			{
				_size = x._size;
				_capaciyu = x.capacity;
				_begin = alloc.allocate(_capacity);
				assign(x._begin, (x.begin + x._size));
			}

			~vector()
			{
				if (this->_begin != NULL || _capacity != 0)
					_alloc.deallocate(_begin, _capacity);
			}

			//Member functions
			
			vector& operator=( const vector& other );
			{
				_size = other._size;
				_capacity = other._capacity;
				_alloc = other._alloc;
				assign(other._begin, other.begin + _size);
				return (*this);
			}

			void assign( size_type count, const T& value );

			template< class InputIt >
			void assign( InputIt first, InputIt last );

			void assign( std::initializer_list<T> ilist );

			allocator_type get_allocator() const;

			//ELEMENT ACCESS
			reference 		at( size_type pos );
			const_reference	at( size_type pos ) const;
			reference 		operator[]( size_type pos );
			const_reference operator[]( size_type pos ) const;
			reference 		front();
			const_reference	front() const;
			reference 		back();
			const_reference	back() const;
			T*				data();
			const T*		data() const;

			//Iterators

			//CONTROLLARE CON DAVIDE

			//CAPACITY
			bool 		empty() const;
			size_type	size() const;
			size_type	max_size() const;
			void 		reserve( size_type new_cap );
			size_type	capacity() const;
			void 		shrink_to_fit();

			//Modifiers

			void clear();

			
	};
}