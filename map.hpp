/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:17:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/12/01 00:04:14 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "utility.hpp"
#include "rb_tree.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map : public RBTreeSet<ft::pair<const Key, T>, Node<ft::pair<const Key, T> >, Compare, Allocator>
	{
		public:
			typedef Key														key_type;
			typedef	T														mapped_type;
			typedef ft::pair<const Key, T>										value_type;
			typedef typename Allocator::template rebind<Node<value_type> >::other		allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef RBIterator<value_type, Compare, Node<value_type> >						iterator;
			typedef RBIterator<value_type, Compare, Node<value_type> >				const_iterator;

			map() {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) {};
			template <class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			{
				this->insert(first, last);
			};
			map(const map& other)
			{
				this->insert(other.begin(), other.end());
			};
			map&	operator=(map const & rhs)
			{
				if (this == &rhs)
					return (*this);
				iterator	first = rhs.begin();
				iterator	end = rhs.end();
				clear();
				while (first != end)
					insert(*first++);
				return (*this);
			}
			~map() { clear(); };

			void	erase(iterator pos)
			{
				this->erase_deep(*pos);
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
					this->erase_deep(*first++);
			}

			size_type	erase(const ft::pair<const Key, T>& key)
			{
				if (erase_deep(key) != this->end())
					return (1);
				return (0);
			}

			iterator	erase_deep(ft::pair<const Key, T> const & val)
			{
				pointer		node = this->find(val).node;
				pointer		tmp;
				pointer		successor;
				pointer		toHandle;
				iterator	ret;
				
				if (!node)
					return (iterator(this->_sentinel, this->_sentinel));
				else if (node != this->_sentinel)
					ret = this->find(this->getSuccessor(node)->data);
				else
					return (iterator(this->_sentinel, this->_sentinel));

				if ((!node->child[LEFT] && !node->child[RIGHT]) || (node->child[LEFT] == this->_sentinel && node->child[RIGHT] == this->_sentinel))
				{
					tmp = node->parent;
					if (node->color == BLACK && node != this->_root)
						this->balanceDelete(node);
					if (tmp != this->_sentinel)
						this->unlink(tmp, node);
					else
					{
						this->_root = this->_sentinel;
						this->_sentinel->parent = this->_root;
					}
				}
				else if (this->oneChild(node) != this->_sentinel)
				{
					if (node->color == BLACK && node != this->_root)
						this->balanceDelete(node);
					this->oneChild(node)->parent = node->parent;
					if (node != this->_root)
						this->link(node->parent, node, this->oneChild(node));
					else
					{
						this->_root = this->oneChild(node);
						this->_sentinel->parent = this->_root;
					}
				}
				else
				{
					toHandle = NULL;
					if (this->_c(node->data.first, this->_root->data.first))
						successor = this->getSuccessor(node);
					else
						successor = this->getPredecessor(node);
					this->balanceDelete(successor);
					if (successor->child[RIGHT] != this->_sentinel)
					{
						toHandle = successor->child[RIGHT];
						successor->child[RIGHT] = this->_sentinel;
					}
					this->unlink(successor->parent, successor);
					this->link(node->parent, node, successor);
					if (node->child[LEFT] != this->_sentinel)
					{
						node->child[LEFT]->parent = successor;
						successor->child[LEFT] = node->child[LEFT];
					}
					if (node->child[RIGHT] != this->_sentinel)
					{
						if (successor->child[RIGHT] != this->_sentinel)
							this->link(successor->parent, successor, successor->child[RIGHT]);
						node->child[RIGHT]->parent = successor;
						successor->child[RIGHT] = node->child[RIGHT];
					}
				}
				this->_alloc.deallocate(node, 1);
				node = NULL;
				this->_size--;
				return (ret);
			}

			iterator	find(ft::pair<const Key, T> const & val) const
			{
				pointer	node = this->_root;

				if (node && node != this->_sentinel)
					return (findPointer(node, val));
				return (iterator(this->_sentinel, this->_sentinel));
			}

			iterator	findPointer(pointer& start, ft::pair<const Key, T> const & val) const
			{
				if (!start || start->color == SENTINEL)
					return (iterator(this->_sentinel, this->_sentinel));
				if (this->_c(val.first, start->data.first) && start->data.first != val.first)
					return (findPointer(start->child[LEFT], val));
				else if (this->_c(start->data.first, val.first) && start->data.first != val.first)
					return (findPointer(start->child[RIGHT], val));
				else
					return (iterator(start, this->_sentinel));
			}

			iterator	insert(iterator position, const value_type& val)
			{
				(void)position;
				insert(val);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

			ft::pair<iterator, bool> insert(ft::pair<const Key, T> const &val)
			{
				ft::pair<iterator, bool> ret;
				pointer	node = new Node<value_type>(val);
				// pointer node = this->_alloc.allocate(1);

				node->color = RED;
				node->parent = this->_sentinel;
				node->child[LEFT] = this->_sentinel;
				node->child[RIGHT] = this->_sentinel;
				// node->data(val.first, val.second);

				if (!this->_size)
				{
					this->_root = node;
					this->_sentinel->parent = node;
					node->color = BLACK;
					this->_size++;
					ret.first = iterator(node, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				else
				{
					ret.first = iterator(node, this->_sentinel);
					ret.second = false;
					if (this->_c(val.first, this->_root->data.first) && this->_root->data.first != val.first)
						return (insertNode(this->_root->child[LEFT], node, this->_root, 1));
					else if (this->_c(this->_root->data.first, val.first) && this->_root->data.first != val.first)
						return (insertNode(this->_root->child[RIGHT], node, this->_root, 1));
					else
					{
						this->_alloc.deallocate(node, 1);
						return (ret);
					}
				}
			}

			ft::pair<iterator, bool> insertNode(pointer &start, pointer &node, pointer& parent, int flag)
			{
				ft::pair<iterator, bool>	ret;
				
				if (!start || start == this->_sentinel)
				{
					node->parent = parent;
					if (this->_c(node->data.first, parent->data.first))
						parent->child[LEFT] = node;
					else
						parent->child[RIGHT] = node;
					start = node;
					if (flag)
						this->_size++;
					this->balanceInsert(start);
					ret.first = iterator(start, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				if (this->_c(node->data.first, start->data.first))
					return (insertNode(start->child[LEFT], node, start, flag));
				else if (this->_c(start->data.first, node->data.first))
					return (insertNode(start->child[RIGHT], node, start, flag));
				ret.first = iterator(node, this->_sentinel);
				delete node;
				ret.second = false;
				return (ret);
			}

			void	clear()
			{
				iterator	iter = this->begin();
				iterator	end = this->end();

				while (iter != end)
					erase(*iter++);
			}
	};
}
