/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:54:03 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/30 17:08:47 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include "utility.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set : public RBTreeSet<Key, Node<Key>, Compare, Alloc>
	{
		public:
			typedef Key														key_type;
			typedef Key														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef typename Alloc::template rebind<Node<Key> >::other		allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef RBIterator<Key, Compare, Node<Key> >						iterator;
			typedef RBIterator<const Key, Compare, Node<Key> >				const_iterator;

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_value_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
			};
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_value_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
				this->insert(first, last);
			};
			set(const set& other)
			{
				this->_key_type = other._key_type;
				this->_value_type = other._value_type;
				this->_key_compare = other._key_compare;
				this->_value_compare = other._value_compare;
				if (other.begin() != other.end())
					this->insert(other.begin(), other.end());
			};
			set&	operator=(const set& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_key_type = rhs._key_type;
				this->_value_type = rhs._value_type;
				this->_key_compare = rhs._key_compare;
				this->_value_compare = rhs._value_compare;
				this->_alloc = rhs._alloc;
				this->clear();
				this->insert(rhs.begin(), rhs.end());
				return (*this);
			};
			virtual ~set() { clear(); }

			iterator	erase(iterator pos)
			{
				iterator	ret = this->getSuccessor(pos.node);

				this->erase_deep(*pos);
				return (ret);
			}

			iterator	erase(iterator first, iterator last)
			{
				while (first != last)
					this->erase_deep(*first++);
				return (last.node);
			}

			size_type	erase(const Key& key)
			{
				if (erase_deep(key) != this->end())
					return (1);
				return (0);
			}

			iterator	erase_deep(Key const & val)
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
					if (this->_c(node->data, this->_root->data))
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

			iterator	find(Key const & val) const
			{
				pointer	node = this->_root;

				if (node && node != this->_sentinel)
					return (findPointer(node, val));
				return (iterator(this->_sentinel, this->_sentinel));
			}

			iterator	findPointer(pointer& start, Key const & val) const
			{
				if (!start || start->color == SENTINEL)
					return (iterator(this->_sentinel, this->_sentinel));
				if (this->_c(val, start->data) && start->data != val)
					return (findPointer(start->child[LEFT], val));
				else if (this->_c(start->data, val) && start->data != val)
					return (findPointer(start->child[RIGHT], val));
				else
					return (iterator(start, this->_sentinel));
			}

			template <class InputIt>
			void						insert(InputIt first, InputIt last)
			{
				while (first != last)
					this->insert(*first++);
			};

			iterator	insert(iterator pos, const Key & val)
			{
				(void)pos;
				return (this->insert(val).first);
			}


			ft::pair<iterator, bool> insert(Key const &val)
			{
				ft::pair<iterator, bool> ret;
				pointer node = this->_alloc.allocate(1);

				node->color = RED;
				node->parent = this->_sentinel;
				node->child[LEFT] = this->_sentinel;
				node->child[RIGHT] = this->_sentinel;
				node->data = val;

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
					if (this->_c(val, this->_root->data) && this->_root->data != val)
						return (insertNode(this->_root->child[LEFT], node, this->_root, 1));
					else if (this->_c(this->_root->data, val) && this->_root->data != val)
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
					if (this->_c(node->data, parent->data))
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
				if (this->_c(node->data, start->data))
					return (insertNode(start->child[LEFT], node, start, flag));
				else if (this->_c(start->data, node->data))
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

	template <class T, class Compare, class Alloc>
	bool operator==(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		typename set<T, Compare, Alloc>::iterator	iter = lhs.begin();
		typename set<T, Compare, Alloc>::iterator	iter2 = rhs.begin();
	
		while (iter != lhs.end())
		{
			if (*iter != *iter2)
				return (0);
			iter++;
			iter2++;
		}
		if (iter2 != rhs.end())
			return (0);
		return (1);
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs < rhs));
	}
}
