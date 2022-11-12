/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:40:11 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/12 20:49:06 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag	{};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct contiguous_iterator_tag : public random_access_iterator_tag {};
	
	template <bool is_valid, typename T>
	struct valid_iterator_tag_res
	{
		typedef T			type;
		const static bool	value = is_valid;
	};

	template <typename T>
	struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_input_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::contiguous_iterator_tag> : public valid_iterator_tag_res<true, ft::contiguous_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};
	
	template <>
	struct is_input_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::output_iterator_tag> : public valid_iterator_tag_res<true, ft::output_iterator_tag> {};

	template <typename T>
	struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_ft_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<std::random_access_iterator_tag> : public valid_iterator_tag_res<true, std::random_access_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<std::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, std::bidirectional_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<std::forward_iterator_tag> : public valid_iterator_tag_res<true, std::forward_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<std::input_iterator_tag> : public valid_iterator_tag_res<true, std::input_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::output_iterator_tag> : public valid_iterator_tag_res<true, ft::output_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<std::output_iterator_tag> : public valid_iterator_tag_res<true, std::output_iterator_tag> {};

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
