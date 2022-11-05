/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:56 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/06 00:47:35 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>

namespace ft
{
	// Iterator tags
	
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag : public random_access_iterator_tag { };


	// Iterator traits

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};


	// Iterator types

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	struct forward_iterator : ft::iterator<ft::forward_iterator_tag, T>
	{
		typedef typename	ft::iterator<ft::forward_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename	ft::iterator<ft::forward_iterator_tag, T>::difference_type		difference_type;
		typedef typename	ft::iterator<ft::forward_iterator_tag, T>::value_type			value_type;
		typedef typename	ft::iterator<ft::forward_iterator_tag, T>::pointer				pointer;
		typedef typename	ft::iterator<ft::forward_iterator_tag, T>::reference			reference;
	};

	template <class T>
	struct bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
	};

	template <class T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			random_access_iterator() {};
			random_access_iterator(pointer p) : _pointed(p) {};
			reference				operator*() const { return (*_pointed); }
			pointer					operator->() { return &(this->operator*()); }
			random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_pointed + n); }
			random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_pointed - n); }
			random_access_iterator&	operator++() { _pointed++; return (*this); }
			random_access_iterator	operator++(int) { random_access_iterator ret(*this); _pointed++; return (ret); }
			random_access_iterator&	operator--() { _pointed--; return (*this); }
			random_access_iterator	operator--(int) { random_access_iterator ret(*this); _pointed--; return (ret); }
			random_access_iterator&	operator+=(difference_type n) { _pointed += n; return (*this); }
			random_access_iterator&	operator-=(difference_type n) { _pointed += n; return (*this); }
			operator				random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->_pointed)); }
			pointer					pointed() { return this->_pointed; };
		private:
			pointer	_pointed;
	};

	template <class T>
	struct contiguous_iterator : ft::iterator<ft::contiguous_iterator_tag, T>
	{
		typedef typename	ft::iterator<ft::contiguous_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename	ft::iterator<ft::contiguous_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<ft::contiguous_iterator_tag, T>::value_type		value_type;
		typedef typename	ft::iterator<ft::contiguous_iterator_tag, T>::pointer			pointer;
		typedef typename	ft::iterator<ft::contiguous_iterator_tag, T>::reference			reference;
	};

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			reverse_iterator() : _elem() {};
			explicit reverse_iterator(iterator_type iter) : _elem(iter) {};
			template <class ReverseIterator>
			reverse_iterator(const reverse_iterator<ReverseIterator>& rev_it) : _elem(rev_it.base()) {};
			reverse_iterator(pointer p) : _pointed(p) {};
			virtual ~reverse_iterator() {};
			iterator_type		base() const { return (_pointed); };
			reference			operator*() const { return (*_pointed); };
			reverse_iterator	operator+(difference_type n) const { return (_pointed + n); };
			reverse_iterator&	operator++() { _pointed++; return (*this); };
			reverse_iterator&	operator++(int) { reverse_iterator ret = *this; this->_pointed++; return (ret); };
			reverse_iterator	operator-(difference_type n) const { return (_pointed - n); };
			reverse_iterator&	operator--() { _pointed--; return (*this); };
			reverse_iterator&	operator--(int) { reverse_iterator ret; this->_pointed--; return (ret); };
			reverse_iterator&	operator+=(difference_type n) { _pointed + n; return (*this); };
			reverse_iterator&	operator-=(difference_type n) { _pointed - n; return (*this); };
			pointer				operator->() const { return &(*_pointed); };
			reference			operator[] (difference_type n) const { return (*(_pointed + n)); };
		private:
			iterator_type	_elem;
			pointer			_pointed;
	};


	
	//Overloads

	template <class InputIterator1, class InputIterator2>
	bool	operator==(InputIterator1 x, InputIterator2 y)
	{
		if (&(*x) == &(*y)) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator!=(InputIterator1 x, InputIterator2 y)
	{
		return (!(x == y));
	}

	template <class InputIterator>
	typename InputIterator::difference_type operator-(InputIterator lhs, InputIterator rhs)
	{
		return (lhs.pointed() - rhs.pointed());
	}

	template <class InputIterator1, class InputIterator2>
	typename InputIterator1::difference_type operator-(InputIterator1 lhs, InputIterator2 rhs)
	{
		return (lhs.pointed() - rhs.pointed());
	}

	//Operations
	template <class InputIterator, class Distance>
	void	advance(InputIterator & it, Distance n);

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	ret = 0;
		
		while (first++ != last)
			ret++;
		return (ret);
	}
}
