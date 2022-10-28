/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:28:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/28 18:04:06 by ddelladi         ###   ########.fr       */
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
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

			//Constructor

			explicit vector (const allocator_type& alloc = allocator_type()):
				_size(0),
				_capacity(0),
				_begin(NULL),
				_end(NULL),
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
					_size = n;
					_capacity = 1;
					while (_capacity < n)
						_capacity *= 2;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
					while (n--)
					{
						_alloc.construct(_end, val);
						_end++;
					}
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
			
			vector& operator=(const vector& other)
			{
				_size = other._size;
				_capacity = other._capacity;
				_alloc = other._alloc;
				assign(other._begin, other.begin + _size);
				return (*this);
			}

			void assign(size_type count, const T& value)
			{
				pointer	it;

				it = _begin;
				while (it != _begin + _size)
				{
					_alloc.destroy(it);
					if (it < _begin + count)
						_alloc.construct(it, value);
					it++;
				}
			};

			// template <class InputIt>
			// void assign(InputIt first, InputIt last);

			// void assign( std::initializer_list<T> ilist );

			allocator_type get_allocator() const;

			//ELEMENT ACCESS
			reference 		at(size_type pos);
			const_reference	at(size_type pos) const;
			reference 		operator[](size_type pos);
			const_reference operator[](size_type pos) const;
			reference 		front();
			const_reference	front() const;
			reference 		back();
			const_reference	back() const;
			T*				data();
			const T*		data() const;



			//Iterators

			iterator				begin() { };
			const_iterator			begin() const;
			const_iterator			cbegin() const;
			iterator				end();
			const_iterator			end() const;
			const_iterator			cend() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			const_reverse_iterator	crbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;
			const_reverse_iterator	crend() const;



			// Vector info
			
			bool 		empty() const { return (size() == 0 ? true : false); };
			size_type	size() const { return (_size); };
			size_type	max_size() const { return (allocator_type().max_size()); };
			void 		reserve(size_type n) {
				pointer		prev_begin = _begin;
				pointer		prev_end = _end;
				size_type	prev_capacity = _capacity;
				size_type	prev_size = _size;
				size_type	new_cap = 1;
				
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > _capacity)
				{
					while (new_cap < n)
						new_cap *= 2;
					_begin = _alloc.allocate(new_cap);
					_end = _begin;
					_capacity = new_cap;
					while (prev_begin != prev_end)
					{
						_alloc.construct(_end, *prev_begin);
						_end++;
						prev_begin++;
					}
					_alloc.deallocate(prev_begin - prev_size, prev_capacity);
				}
			};
			size_type	capacity() const { return (_capacity); };


			//Modifiers

			void clear();

		private:
			size_type											_size;
			size_type											_capacity;
			pointer												_begin;
			pointer												_end;
			allocator_type										_alloc;
			
	};
}