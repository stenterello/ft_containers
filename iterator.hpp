/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:56 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/08 12:57:38 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>

namespace ft
{
	// Iterator tags

	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};
	struct contiguous_iterator_tag : public random_access_iterator_tag
	{
	};

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
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T							*pointer;
		typedef T							&reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T							*pointer;
		typedef T							&reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// Iterator types

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
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
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference			reference;
	};

	template <class T>
	struct bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
	};

	template <class T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
		random_access_iterator(){};
		random_access_iterator(pointer p) : _pointed(p){};
		random_access_iterator(random_access_iterator const &src) { this->_pointed = src.pointed(); }
		virtual ~random_access_iterator(){};
		reference				operator*() const { return (*_pointed); }
		pointer					operator->() { return &(this->operator*()); }
		random_access_iterator	operator+(difference_type n) const { return (_pointed + n); }
		random_access_iterator	operator-(difference_type n) const { return (_pointed - n); }
		random_access_iterator&	operator++()
		{
			_pointed++;
			return (*this);
		}
		random_access_iterator	operator++(int)
		{
			random_access_iterator ret(*this);
			_pointed++;
			return (ret);
		}
		random_access_iterator&	operator--()
		{
			_pointed--;
			return (*this);
		}
		random_access_iterator	operator--(int)
		{
			random_access_iterator ret(*this);
			_pointed--;
			return (ret);
		}
		random_access_iterator&	operator+=(difference_type n)
		{
			_pointed += n;
			return (*this);
		}
		random_access_iterator&	operator-=(difference_type n)
		{
			_pointed -= n;
			return (*this);
		}
		bool					operator==(random_access_iterator const &rhs)
		{
			if (this->pointed() == rhs.pointed())
				return true;
			return false;
		}
		bool					operator!=(random_access_iterator const &rhs)
		{
			if (this->pointed() == rhs.pointed())
				return false;
			return true;
		}
		operator 				random_access_iterator<const T>() const { return (random_access_iterator<const T>(this->_pointed)); }
		pointer 				pointed() const { return this->_pointed; }
		reference 				operator[](difference_type n) { return (*(_pointed + n)); }
		difference_type 		operator-(random_access_iterator const &rhs) const { return (this->pointed() - rhs.pointed()); }
		difference_type 		operator+(random_access_iterator const &rhs) const { return (this->pointed() + rhs.pointed()); }

	private:
		pointer _pointed;
	};

	template <class T>
	struct contiguous_iterator : ft::iterator<ft::contiguous_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::reference			reference;
	};

	template <class InputIterator>
	class reverse_iterator : ft::iterator<typename InputIterator::iterator_category, typename InputIterator::value_type>
	{
	public:
		typedef InputIterator iterator_type;
		typedef typename ft::iterator_traits<InputIterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<InputIterator>::value_type			value_type;
		typedef typename ft::iterator_traits<InputIterator>::pointer			pointer;
		typedef typename ft::iterator_traits<InputIterator>::reference			reference;
		typedef typename ft::iterator_traits<InputIterator>::iterator_category	iterator_category;
		reverse_iterator() : _base(NULL){};
		explicit reverse_iterator(iterator_type iter) : _base(iter){};
		template <class ReverseIterator>
		reverse_iterator(const reverse_iterator<ReverseIterator> &rev_it) : _base(rev_it.base()){};
		virtual ~reverse_iterator(){};
		iterator_type base() const { return (_base); };
		reference			operator*() const { return (*(_base - 1)); };
		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator(_base - n);
		};
		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(_base + n);
		};
		reverse_iterator&	operator++()
		{
			_base--;
			return (*this);
		};
		reverse_iterator	operator++(int)
		{
			reverse_iterator ret(*this);
			this->_base--;
			return (ret);
		};
		reverse_iterator&	operator--()
		{
			_base++;
			return (*this);
		};
		reverse_iterator	operator--(int)
		{
			reverse_iterator ret(*this);
			this->_base++;
			return (ret);
		};
		reverse_iterator&	operator+=(difference_type n)
		{
			_base -= n;
			return (*this);
		};
		reverse_iterator&	operator-=(difference_type n)
		{
			_base += n;
			return (*this);
		};
		pointer				operator->() const { return &(*(_base - 1)); };
		reference			operator[](difference_type n) const { return (*(_base - n - 1)); };
		difference_type 	operator+(reverse_iterator const &rhs) const { return (this->base() + rhs.base()); }
		difference_type 	operator-(reverse_iterator const &rhs) const { return (rhs.base() - this->base()); }
	private:
		iterator_type _base;
	};

	// Overloads

	template <class InputIterator>
	bool	operator<(reverse_iterator<InputIterator> const lhs, reverse_iterator<InputIterator> const rhs)
	{
		if (lhs.base() > rhs.base()) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<(reverse_iterator<InputIterator1> const lhs, reverse_iterator<InputIterator2> const rhs)
	{
		if (lhs.base() > rhs.base()) return true;
		return false;
	}

	template <class InputIterator>
	bool	operator<=(reverse_iterator<InputIterator> const lhs, reverse_iterator<InputIterator> const rhs)
	{
		if (lhs.base() >= rhs.base()) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<=(reverse_iterator<InputIterator1> const lhs, reverse_iterator<InputIterator2> const rhs)
	{
		if (lhs.base() >= rhs.base()) return true;
		return false;
	}

	template <class InputIterator>
	bool	operator>(reverse_iterator<InputIterator> const lhs, reverse_iterator<InputIterator> const rhs)
	{
		if (lhs.base() < rhs.base()) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>(reverse_iterator<InputIterator1> const lhs, reverse_iterator<InputIterator2> const rhs)
	{
		if (lhs.base() < rhs.base()) return true;
		return false;
	}

	template <class InputIterator>
	bool	operator>=(reverse_iterator<InputIterator> const lhs, reverse_iterator<InputIterator> const rhs)
	{
		if (lhs.base() <= rhs.base()) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>=(reverse_iterator<InputIterator1> const lhs, reverse_iterator<InputIterator2> const rhs)
	{
		if (lhs.base() <= rhs.base()) return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator==(InputIterator1 x, InputIterator2 y)
	{
		if (&(*x) == &(*y))
			return true;
		return false;
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator!=(InputIterator1 x, InputIterator2 y)
	{
		return (!(x == y));
	}

	template <class InputIterator>
	InputIterator operator+(int n, InputIterator rhs)
	{
		return (rhs + n);
	}

	template <class InputIterator>
	bool	operator>(InputIterator lhs, InputIterator rhs)
	{
		if (lhs.pointed() > rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>(InputIterator1 lhs, InputIterator2 rhs)
	{
		if (lhs.pointed() > rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator>
	bool	operator>=(InputIterator lhs, InputIterator rhs)
	{
		if (lhs.pointed() >= rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator>=(InputIterator1 lhs, InputIterator2 rhs)
	{
		if (lhs.pointed() >= rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator>
	bool	operator<(InputIterator lhs, InputIterator rhs)
	{
		if (lhs.pointed() < rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<(InputIterator1 lhs, InputIterator2 rhs)
	{
		if (lhs.pointed() < rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator>
	bool	operator<=(InputIterator lhs, InputIterator rhs)
	{
		if (lhs.pointed() <= rhs.pointed())
			return (true);
		return (false);
	}

	template <class InputIterator1, class InputIterator2>
	bool	operator<=(InputIterator1 lhs, InputIterator2 rhs)
	{
		if (lhs.pointed() <= rhs.pointed())
			return (true);
		return (false);
	}


	// Operations

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}

	template <class InputIterator1, class InputIterator2>
	typename ft::iterator_traits<InputIterator1>::difference_type
	distance(InputIterator1 first, InputIterator2 last)
	{
		typename ft::iterator_traits<InputIterator1>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}
}
