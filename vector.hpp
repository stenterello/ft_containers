/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:28:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/02 14:34:01 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"

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
			{}

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
			}

			vector& operator=(const vector& other)
			{
				_size = other.size();
				_capacity = other.capacity();
				_alloc = other.get_allocator();
				assign(other.begin(), other.begin() + _size);
				return (*this);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
				_alloc(alloc)
			{
				bool	is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value;
				if (!is_valid)
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>();
				difference_type n = ft::distance(first, last);
				_size = n;
				_capacity = 1;
				while (_capacity < static_cast<unsigned long>(n))
					_capacity *= 2;
				_begin = _alloc.allocate(_capacity);
				_end = _begin;
				while (n--)
				{
					_alloc.construct(_end, *first);
					_end++;
					first++;
				}
			}

			vector (const vector& x)
			{
				_size = x.size();
				_capacity = x.capacity();
				_begin = _alloc.allocate(x.capacity());
				assign(x.begin(), x.end());
				_end = _begin + _size;
			}

			~vector()
			{
				if (this->_begin != NULL || _capacity != 0)
					_alloc.deallocate(_begin, _capacity);
			}


			//Member functions

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

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				bool	is_valid;

				is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value;
				if (!is_valid)
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>();
				if (ft::distance(first, last) > static_cast<long>(_capacity))
					this->reserve(ft::distance(first, last));
				iterator	iter = this->begin();
				while (first != last)
				{
					_alloc.construct(&(*iter), *first);
					iter++;
				}
			};

			// void assign( std::initializer_list<T> ilist );

			void			reserve(size_type n)
			{
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

			void	resize(size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw std::length_error("vector::resize");
				else if (n > _capacity)
				{
					this->reserve(n);
					n -= this->size();
					while (n--)
						_alloc.construct(_end++, val);
					_size += n;
				}
				else if (n > _size)
				{
					n -= this->size();
					while (n--)
						_alloc.construct(_end++, val);
					_size += n;
				}
				else
				{
					pointer	p = _begin + n;
					while (p != _end)
						_alloc.destroy(p++);
					_end = p;
					_capacity = n;
					_size = n;
				}
			}

			void	push_back(const value_type& val)
			{
				if (_size == _capacity && _capacity + 1 > this->max_size())
					throw std::length_error("vector::push_back");
				if (_size == _capacity)
					this->reserve(_size + 1);
				assign(_size, val);
				_size++;
				_end++;
			}

			void	pop_back()
			{
				if (this->empty())
					return ;
				iterator	iter = this->end() - 1;
				_alloc.destroy(&(*iter));
				_size--;
				_end--;

			}

			iterator	insert(iterator position, const value_type& val)
			{
				if (_size == _capacity && _capacity + 1 > this->max_size())
					throw std::length_error("vector::insert");
				if (_size == _capacity)
					this->reserve(_size + 1);
				ft::vector<T>	tmp = *this;
				iterator		iter2 = tmp.begin();
				iterator		iter3 = position;
				while (&(*iter2) - &(*tmp.begin()) != &(*position) - &(*this->begin()))
					iter2++;
				*position = val;
				insert(++position, iter2, tmp.end());
				return (iter3);
			}

			void		insert(iterator position, size_type n, const value_type& val)
			{
				if (_size + n > this->max_size())
					throw std::length_error("vector::insert");
				if (_size + n > _capacity)
					this->reserve(n);
				ft::vector<T>	tmp;
				iterator		iter2 = tmp.begin();
				while (&(*iter2) - &(*tmp.begin()) != &(*position) - &(*this->begin()))
					iter2++;
				insert(position + n, iter2, tmp.end());
				while (n--)
					*position++ = val;
				_end += n;
				_size += n;
			}

			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				bool	is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value;
				if (!is_valid)
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>();
				if (this->size() + distance(first, last) > this->max_size())
					throw std::length_error("vector::insert");
				if (this->capacity() < this->size() + distance(first, last))
					this->reserve(this->size() + distance(first, last));
				_end += ft::distance(first, last);
				_size += ft::distance(first, last);
				while (first != last)
					*position++ = *first++;
			}

			iterator	erase(iterator position)
			{
				ft::vector<T>	tmp = *this;
				iterator		iter = tmp.begin();
				while (&(*iter) - &(*tmp.begin()) != &(*position) - &(*this->begin()))
					iter++;
				_alloc.destroy(&(*position));
				insert(position, iter, tmp.end());
				_alloc.destroy(_end);
				_size--;
				_end--;
				return (position + 1);
			}

			iterator	erase(iterator first, iterator last)
			{
				vector<T>	tmp;
				iterator		iter = tmp.begin();
				iterator		tmp_iter = first;
				while (&(*iter) - &(*tmp.begin()) != &(*last) - &(*this->begin()))
					iter++;
				while (first != last)
					_alloc.destroy(&(*first++));
				insert(tmp_iter, iter, tmp.end());
				_size -= ft::distance(first, last);
				_end -= ft::distance(first, last);
				return (tmp_iter + ft::distance(iter, tmp.end()));
			}

			void	swap(vector& x)
			{
				ft::vector<T>	tmp;

				tmp = x;
				x = *this;
				*this = tmp;
			}

			void	clear()
			{
				iterator	iter = this->begin();

				while (_size--)
				{
					_alloc.destroy(&(*iter));
					iter++;
				}
			}


			//Element access

			reference 		at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (*(_begin + pos));
			};

			const_reference	at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (*(_begin + pos));
			};

			reference 		operator[](size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (*(_begin + pos));
			};

			const_reference operator[](size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (*(_begin + pos));
			};
			
			reference 		front() { return (*_begin); };
			const_reference	front() const { return (*_begin); };
			reference 		back() { return (*(_end - 1)); };
			const_reference	back() const { return (*(_end - 1)); };
			T*				data() { return (_begin); };
			const T*		data() const { return (_begin); };



			//Iterators

			iterator				begin() { return (_begin); };
			const_iterator			begin() const { return (_begin); };
			iterator				end() { return (_end); };
			const_iterator			end() const { return (_end); };
			reverse_iterator		rbegin() { return (_end); };
			const_reverse_iterator	rbegin() const { return (_end); };
			reverse_iterator		rend() { return (_begin); };
			const_reverse_iterator	rend() const { return (_begin); };



			// Vector info
			
			bool 			empty() const { return (size() == 0 ? true : false); };
			size_type		size() const { return (_size); };
			size_type		max_size() const { return (allocator_type().max_size()); };
			size_type		capacity() const { return (_capacity); };
			allocator_type	get_allocator() const { return (_alloc); };


		private:
			size_type											_size;
			size_type											_capacity;
			pointer												_begin;
			pointer												_end;
			allocator_type										_alloc;
			
	};

	//Overloads
	template <class T, class Alloc>
	bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T>::const_iterator	iter = lhs.begin();
		typename vector<T>::const_iterator	iter2 = rhs.begin();
		while (iter != lhs.end())
		{
			if (iter2 == rhs.end() || *iter != *iter2)
				return (false);
			iter++;
			iter2++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <class T, class Alloc>
	bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}
