/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:53:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/16 18:39:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <utility>
#include <iostream>
#include "utility.hpp"
#include "iterator.hpp"

namespace ft
{
	enum node_color
	{
		RED = true,
		BLACK = false
	};

	enum branch
	{
		LEFT,
		RIGHT
	};

	template <typename T>
	struct Node
	{
		node_color color;
		Node *parent;
		Node *child[2];
		T data;
	};

	template <class Key, class NodeType, class Compare = std::less<Key>>
	class RBTreeSet
	{

	public:
		typedef std::allocator<NodeType> allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef NodeType *pointer;
		typedef const NodeType *const_pointer;
		typedef RBIterator<Key, Compare, NodeType> iterator;
		typedef RBIterator<const Key, Compare, NodeType> const_iterator;
		
		RBTreeSet() : _root(NULL),
					  _size(0),
					  _alloc(allocator_type()),
					  _sentinel(NULL)
		{};

		RBTreeSet(RBTreeSet const &src) : _root(src._root),
										  _size(src._size),
										  _alloc(src._alloc),
										  _sentinel(src._sentinel)
		{};

		RBTreeSet &operator=(RBTreeSet const &rhs)
		{
			if (this == &rhs)
				return (*this);
			this->_root = rhs._root;
			this->_alloc = rhs._alloc;
			this->_c = rhs._c;
			this->_size = rhs._size;
			this->_sentinel = rhs._sentinel;
			return (*this);
		};

		~RBTreeSet()
		{
			// deallocazione da scrivere (cancella solo la root))
			this->clear();
			_alloc.deallocate(_sentinel, 1);
		};

		bool empty() const { return ((!this->_size) ? true : false); }
		size_type size() const { return this->_size; }
		size_type max_size() const { return _alloc.max_size(); }

		size_type	count(pointer const &node) const
		{
			if (!node)
				return (0);
			size_type ret = 1;
			ret += count(node->child[LEFT]);
			ret += count(node->child[RIGHT]);
			return (ret);
		}

		size_type	count() const
		{
			if (!_root)
				return (0);
			size_type ret = 1;
			ret += count(_root->child[LEFT]);
			ret += count(_root->child[RIGHT]);
			return (ret);
		}

		pointer begin() { return (_root); }
		const_pointer begin() const { return (_root); }

		ft::pair<iterator, bool> insert(Key const &val)
		{
			ft::pair<iterator, bool> ret;
			pointer node = _alloc.allocate(1);

			node->color = RED;
			node->parent = _sentinel;
			node->child[LEFT] = _sentinel;
			node->child[RIGHT] = _sentinel;
			node->data = val;

			if (!_size)
			{
				_root = node;
				node->color = BLACK;
				_size++;
				ret.first = iterator(node, _sentinel);
				ret.second = true;
				return (ret);
			}
			else
			{
				ret.first = iterator(_sentinel, _sentinel);
				ret.second = false;
				if (_c(val, _root->data))
					return (insertNode(_root->child[LEFT], node, _root));
				else if (_c(_root->data, val))
					return (insertNode(_root->child[RIGHT], node, _root));
				else
				{
					_alloc.deallocate(node, 1);
					return (ret);
				}
			}
		}

		ft::pair<iterator, bool> insertNode(pointer &start, pointer &node, pointer& parent)
		{
			ft::pair<iterator, bool>	ret;
			
			if (!start)
			{
				node->parent = parent;
				if (_c(node->data, parent->data))
					parent->child[LEFT] = node;
				else
					parent->child[RIGHT] = node;
				start = node;
				_size++;
				ret.first = iterator(start, _sentinel);
				ret.second = true;
				return (ret);
			}
			if (_c(node->data, start->data))
				return (insertNode(start->child[LEFT], node, start));
			else if (_c(start->data, node->data))
				return (insertNode(start->child[RIGHT], node, start));
			delete node;
			ret.first = iterator(_sentinel, _sentinel);
			ret.second = false;
			return (ret);
		}

		// Se non trova l'elemento, ritorna un puntatore a _sentinel che, in caso venga stampato,
		// produce segmentation fault. Basta inserire all'interno di Set un controllo che l'iteratore
		// non punti a NULL

		iterator	find(Key const & val)
		{
			pointer	node = _root;

			if (node)
				return (findPointer(node, val));
			return (iterator(_sentinel, _sentinel));
		}

		iterator	findPointer(pointer& start, Key const & val)
		{
			if (!start)
				return (iterator(_sentinel, _sentinel));
			if (_c(val, start->data))
				return (findPointer(start->child[LEFT], val));
			else if (_c(start->data, val))
				return (findPointer(start->child[RIGHT], val));
			else
				return (iterator(start, _sentinel));
		}

		pointer	getPredecessor(pointer const & node)
		{
			pointer	tmp = node;
			
			if (tmp->child[LEFT])
				return (max(tmp->child[LEFT]));
			else
			{
				while (tmp->parent != _sentinel)
				{
					if (tmp->parent->child[RIGHT] == tmp)
					{
						tmp = tmp->parent;
						break ;
					}
					tmp = tmp->parent;
				}
				return (tmp);
			}
		}

		pointer	getSuccessor(pointer const & node)
		{
			pointer	tmp = node;
			
			if (tmp->child[RIGHT])
				return (min(tmp->child[RIGHT]));
			else
			{
				while (tmp->parent != _sentinel)
				{
					if (tmp->parent->child[LEFT] == tmp)
					{
						tmp = tmp->parent;
						break ;
					}
					tmp = tmp->parent;
				}
				return (tmp);
			}
		}

		pointer	min() const
		{
			pointer	node = _root;

			if (!node)
				return (NULL);

			while (node->child[LEFT])
				node = node->child[LEFT];
			return (node);
		}

		pointer min(pointer const & node) const
		{
			pointer	tmp = node;

			if (!node)
				return (NULL);

			while (tmp->child[LEFT])
				tmp = tmp->child[LEFT];
			return (tmp);
		}

		pointer	max() const
		{
			pointer	node = _root;

			while (node->child[RIGHT])
				node = node->child[RIGHT];
			return (node);
		}

		pointer	max(pointer const & node) const
		{
			pointer	tmp = node;

			while (tmp->child[RIGHT])
				tmp = tmp->child[RIGHT];
			return (tmp);
		}

		void	erase(Key const & val)
		{
			pointer	node = find(val).node;
			
			if (!node)
				return ;
			pointer	nodeChild = getOnlyChildWithoutChildren(node);
			if (!node->child[LEFT] && !node->child[RIGHT])
			{
				if (node->parent)
				{
					if (node->parent->child[LEFT] == node)
						node->parent->child[LEFT] = _sentinel;
					else
						node->parent->child[RIGHT] = _sentinel;
				}
				else
				{
					_alloc.deallocate(node, 1);
					_root = _sentinel;
					_size--;
					return ;
				}
			}
			else if (nodeChild)
			{
				if (node->parent)
				{
					nodeChild->parent = node->parent;
					if (node->parent->child[LEFT] == node)
						node->parent->child[LEFT] = nodeChild;
					else
						node->parent->child[RIGHT] = nodeChild;
				}
				else
				{
					_root = nodeChild;
					nodeChild->parent = _sentinel;
				}
			}
			else
			{
				pointer	newParent = getSuccessor(node);
				if (node->parent)
				{
					if (node->parent->child[LEFT] == node)
						node->parent->child[LEFT] = newParent;
					else
						node->parent->child[RIGHT] = newParent;
				}
				else
				{
					if (newParent->parent != node)
					{
						if (newParent->parent->child[LEFT] == newParent)
							newParent->parent->child[LEFT] = _sentinel;
						else
							newParent->parent->child[RIGHT] = _sentinel;
						newParent->parent->parent = newParent;
						newParent->child[LEFT] = node->child[LEFT];
						newParent->child[RIGHT] = node->child[RIGHT];
					}
					_root = newParent;
					newParent->parent = _sentinel;
					_alloc.deallocate(node, 1);
					_size--;
					return ;
				}
				if (newParent->parent->child[LEFT] == newParent)
					newParent->parent->child[LEFT] = _sentinel;
				else
					newParent->parent->child[RIGHT] = _sentinel;
				newParent->parent = node->parent;
				newParent->child[LEFT] = node->child[LEFT];
				newParent->child[RIGHT] = node->child[RIGHT];
				if (node->child[LEFT])
					node->child[LEFT]->parent = newParent;
				if (node->child[RIGHT])
					node->child[RIGHT]->parent = newParent;
			}
			_alloc.deallocate(node, 1);
			node = NULL;
			_size--;
		}

		void	clear()
		{
			while (min())
			{
				erase(min()->data);
				std::cout << "size: " << count() << std::endl;
			}
		}

	private:
		pointer _root;
		pointer _sentinel;
		size_type _size;
		allocator_type _alloc;
		Compare _c;

		pointer	getOnlyChildWithoutChildren(pointer const & node)
		{
			pointer	child;

			if (node->child[LEFT] && !node->child[RIGHT])
				child = node->child[LEFT];
			else if (!node->child[LEFT] && node->child[RIGHT])
				child = node->child[RIGHT];
			else
				return (NULL);
			if (child->child[LEFT] || child->child[RIGHT])
				return (NULL);
			return (child);
		}

		pointer&	getOnlyChild(pointer & node)
		{
			if (node->child[LEFT] && !node->child[RIGHT])
				return (node->child[LEFT]);
			else
				return (node->child[RIGHT]);
		}

		void	substituteChild(pointer & parent, pointer & oldSon, pointer & newChild)
		{
			if (parent->child[LEFT] == oldSon)
				parent->child[LEFT] = newChild;
			else
				parent->child[RIGHT] = newChild;
		}

		void	warnChildren(pointer & src, pointer & dst)
		{
			if (src->child[LEFT])
				src->child[LEFT]->parent = dst;
			if (src->child[RIGHT])
				src->child[RIGHT]->parent = dst;
		}

		void	adoptChildren(pointer & src, pointer & dst)
		{
			dst->child[LEFT] = src->child[LEFT];
			dst->child[RIGHT] = src->child[RIGHT];
		}
	};
}
