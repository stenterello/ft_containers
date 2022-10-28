/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:56 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/28 17:46:01 by ddelladi         ###   ########.fr       */
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
	struct random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
		typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename	ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
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
		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		iterator_type														iter_type;
		reverse_iterator() : iter_type() {};
		explicit reverse_iterator(iterator_type iter) : iter_type(iter) {};
		template <class ReverseIterator>
		reverse_iterator(const reverse_iterator<ReverseIterator>& rev_it) : iter_type(rev_it.base()) {};
		virtual ~reverse_iterator() {};
		iterator_type		base() const;
		reference			operator*() const;
		reverse_iterator	operator+(difference_type n) const;
		reverse_iterator&	operator++();
		reverse_iterator&	operator++(int);
		reverse_iterator	operator-(difference_type n) const;
		reverse_iterator&	operator--();
		reverse_iterator&	operator--(int);
		reverse_iterator&	operator+=(difference_type n);
		reverse_iterator&	operator-=(difference_type n);
		pointer				operator->() const;
		reference			operator[] (difference_type n) const;
	};


	
	//Overloads

	//Operations
	template <class InputIterator, class Distance>
	void	advance(InputIterator & it, Distance n);
}