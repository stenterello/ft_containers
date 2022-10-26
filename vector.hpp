/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:28:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/26 17:36:18 by ddelladi         ###   ########.fr       */
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
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef iterator									iterator;
			//iterator
			//const_iterator
			//reverse_iterator
			//const_reverse_iterator

			//Exceptions

			class length_error : public std::exception
			{
				public:
					virtual const char * what() const throw()
					{
						return ("ft::length_error: vector");
					}
			};

			//Constructor

			explicit vector (const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_alloc(alloc)
			{
				std::cout << "Default" << std::endl;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_alloc(alloc)
			{
				if (n > 0)
				{
					_capacity = 1;
					while (_capacity < n)
						_capacity *= 2;
					_begin = _alloc.allocate(_capacity);
					for (size_t i = 0; i < n; i++)
					{
						_begin[i] = val;
						std::cout << _begin[i] << std::endl;
					}
					std::cout << _capacity << std::endl;
				}
				std::cout << "Constructor" << std::endl;
			}

			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
			// 	_size(0),
			// 	_capacity(0),
			// 	_begin(NULL),
			// 	_alloc(alloc)
			// {
			// 	assign(first, last);
			// }

			vector (const vector& x)
			{
				_size = x._size;
				_capacity = x.capacity;
				_begin = _alloc.allocate(_capacity);
				assign(x._begin, (x.begin + x._size));
			}

			~vector()
			{
				if (this->_begin != NULL || _capacity != 0)
					_alloc.deallocate(_begin, _capacity);
			}

			//Member functions
			
			vector& operator=( const vector& other )
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

			// void assign( std::initializer_list<T> ilist );

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

			iterator begin();
			const_iterator begin() const;
			const_iterator cbegin() const;
			iterator end();
			const_iterator end() const;
			const_iterator cend() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			const_reverse_iterator crbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_reverse_iterator crend() const;

			//CAPACITY
			bool 		empty() const;
			size_type	size() const;
			size_type	max_size() const;
			void 		reserve( size_type new_cap );
			size_type	capacity() const;
			void 		shrink_to_fit();

			//Modifiers

			void clear();

			//Iterators
			iterator()
			{
				iterator::value_type = this.value_type;
				iterator::difference_type = this.difference_type;
				iterator::pointer = NULL;
				iterator::reference = this.reference;
				iterator::iterator_category = this.iterator_category;
			}

		private:
			size_type											_size;
			size_type											_capacity;
			pointer												_begin;
			pointer												_end;
			allocator_type										_alloc;
			
	};
}