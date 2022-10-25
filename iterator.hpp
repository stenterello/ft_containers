/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:56 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/25 18:52:06 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag : public random_access_iterator_tag { };

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

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	//Overloads
	template <class InputIterator>
	InputIterator&	operator++();

	//Operations
	template <class InputIterator, class Distance>
	void	advance(InputIterator & it, Distance n);


	//Reverse Iterator
	template <class Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
											typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator	current;
		public:
			typedef Iterator				iterator;
			typedef typename iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator>::reference		reference;
			typedef typename iterator_traits<Iterator>::pointer			pointer;
			typedef typename iterator_traits<Iterator>::value_type		value_type;

			reverse_iterator();
			explicit reverse_iterator(Iterator src);

			Iterator	getCurrent() const;

	};

	//Const Reverse Iterator
	template <class Iterator>
	class const_reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
													typename iterator_traits<Iterator>::value_type,
													typename iterator_traits<Iterator>::difference_type,
													typename iterator_traits<Iterator>::pointer,
													typename iterator_traits<Iterator>::reference>
	{

	};
}

#include "iterator.tpp"