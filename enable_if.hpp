/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:11:26 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/29 17:06:26 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T			type;
		static const bool	value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};

	template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};

	template <>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template <>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};

	template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};

	template <>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template <>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template <>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

	template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> {};

	template <bool is_valid, typename T>
	struct valid_iterator_tag_res
	{
		typedef T			type;
		const static bool	value = is_valid;
	};

	template <typename T>
	struct iterator_is_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct iterator_is_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

	template <>
	struct iterator_is_tagged<ft::contiguous_iterator_tag> : public valid_iterator_tag_res<true, ft::contiguous_iterator_tag> {};

	template <>
	struct iterator_is_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct iterator_is_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};
	
	template <>
	struct iterator_is_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

	template <>
	struct iterator_is_tagged<ft::output_iterator_tag> : public valid_iterator_tag_res<true, ft::output_iterator_tag> {};

	template <typename T>
	class InvalidIteratorException : public std::exception
	{
		private:
			std::string	_msg;
		public:
			InvalidIteratorException() throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
			InvalidIteratorException(const InvalidIteratorException&) throw() {};
			InvalidIteratorException&	operator=(const InvalidIteratorException&) throw() {};
			virtual ~InvalidIteratorException() throw() {};
			virtual const char * what() const throw() { return (_msg.c_str()); }
	};
}
