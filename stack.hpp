/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:35:25 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/08 16:45:22 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"
#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef Container					container_type;
			typedef Container::value_type		value_type;
			typedef Container::size_type		size_type;
			typedef Container::reference		reference;
			typedef	Container::const_reference	const_reference;

			explicit stack(const Container& cont = Container()) {};
			stack(const stack& other) {};
			stack&	operator=(const stack& other) {};
			virtual ~stack() {};


			// Element access
			
			reference		top() {};
			const_reference	top() const {};


			// Capacity

			bool		empty() const {};
			size_type	size() const {};


			// Modifiers

			void	push(const value_type& value) {};
			void	pop() {};

		protected:
			Container	c;
	};

	bool	operator==(stack const & lsh, stack const & rhs) {};
	bool	operator!=(stack const & lsh, stack const & rhs) {};
	bool	operator<(stack const & lsh, stack const & rhs) {};
	bool	operator<=(stack const & lsh, stack const & rhs) {};
	bool	operator>(stack const & lsh, stack const & rhs) {};
	bool	operator>=(stack const & lsh, stack const & rhs) {};
}
