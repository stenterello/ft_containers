/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:53:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/19 19:55:21 by ddelladi         ###   ########.fr       */
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

	template <class Key, class NodeType, class Compare = std::less<Key> >
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
			pointer	successor;
			pointer	toHandle;
			
			if (!node)
				return ;
			
			if (!node->child[LEFT] && !node->child[RIGHT])
			{
				link(node->parent, node, _sentinel);
				if (node->color == BLACK && node != _root)
					balanceDelete(node);
			}
			else if (oneChild(node))
			{
				oneChild(node)->parent = node->parent;
				link(node->parent, node, oneChild(node));
			}
			else
			{
				successor = getSuccessor(node);
				if (successor->child[RIGHT])
				{
					toHandle = successor->child[RIGHT];
					successor->child[RIGHT] = _sentinel;
				}
				unlink(successor->parent, successor);
				link(node->parent, node, successor);
				if (node->child[LEFT])
				{
					node->child[LEFT]->parent = successor;
					successor->child[LEFT] = node->child[LEFT];
				}
				if (node->child[RIGHT])
				{
					if (successor->child[RIGHT])
						link(successor->parent, successor, successor->child[RIGHT]);
					node->child[RIGHT]->parent = successor;
					successor->child[RIGHT] = node->child[RIGHT];
				}
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
		pointer			_root;
		pointer			_sentinel;
		size_type		_size;
		allocator_type	_alloc;
		Compare			_c;

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

		pointer*	rotateLeft(pointer & node)
		{
			pointer		toHandle;
			pointer*	tmp = &node;
			pointer*	ret;

			if ((*tmp)->child[RIGHT]->child[LEFT])
				toHandle = (*tmp)->child[RIGHT]->child[LEFT];
			else
				toHandle = NULL;
			if ((*tmp) == _root)
			{
				_root = (*tmp)->child[RIGHT];
				(*tmp)->child[RIGHT]->parent = _sentinel;
			}
			else
			{
				(*tmp)->child[RIGHT]->parent = (*tmp)->parent;
				if ((*tmp)->parent->child[RIGHT] == *tmp)
					(*tmp)->parent->child[RIGHT] = (*tmp)->child[RIGHT];
				else
					(*tmp)->parent->child[LEFT] = (*tmp)->child[RIGHT];
			}
			(*tmp)->parent = (*tmp)->child[RIGHT];
			(*tmp)->child[RIGHT]->child[LEFT] = (*tmp);
			(*tmp) = (*tmp)->child[RIGHT];
			(*tmp)->child[LEFT]->child[RIGHT] = _sentinel;
			if (toHandle)
				insertNode((*tmp), toHandle, (*tmp));
			ret = &(*tmp)->child[LEFT];
			return (&node);
		}

		pointer*	rotateRight(pointer & node)
		{
			pointer	toHandle;
			pointer*	tmp = &node;
			pointer*	ret;

			if ((*tmp) && (*tmp)->child[LEFT] && (*tmp)->child[LEFT]->child[RIGHT])
				toHandle = (*tmp)->child[LEFT]->child[RIGHT];
			else
				toHandle = NULL;
			if ((*tmp) == _root)
			{
				_root = (*tmp)->child[LEFT];
				(*tmp)->child[LEFT]->parent = _sentinel;
			}
			else
			{
				(*tmp)->child[LEFT]->parent = (*tmp)->parent;
				(*tmp)->parent->child[RIGHT] = (*tmp)->child[LEFT];
			}
			(*tmp)->parent = (*tmp)->child[LEFT];
			(*tmp)->child[LEFT]->child[RIGHT] = (*tmp);
			(*tmp) = (*tmp)->child[LEFT];
			(*tmp)->child[RIGHT]->child[LEFT] = _sentinel;
			if (toHandle)
				insertNode((*tmp), toHandle, (*tmp));
			ret = &(*tmp)->child[RIGHT];
			return (ret);
		}

		void	balanceDelete(pointer & node)
		{
			pointer*	tmp = &node;
			pointer		sibling;
			pointer		leftNephew;
			pointer		rightNephew;

			while ((*tmp) != _root && (*tmp)->color == BLACK)
			{
				getRelatives2((*tmp), sibling, leftNephew, rightNephew);
				pointer parent = (*tmp)->parent;
				if (sibling && sibling->color == RED)
				{
					parent->color = RED;
					sibling->color = BLACK;
					if (parent->child[LEFT] == (*tmp))
						rotateLeft(parent);
					else
						rotateRight(parent);
					break ;
				}
				else if (parent->color == BLACK && sibling && sibling->color == BLACK && sibling->child[LEFT] && sibling->child[LEFT]->color == BLACK && sibling->child[RIGHT] && sibling->child[RIGHT]->color == BLACK)
				{
					sibling->color = RED;
					tmp = &parent;
				}
				else if (parent->color == RED && sibling && sibling->color == BLACK && sibling->child[LEFT] && sibling->child[LEFT]->color == BLACK && sibling->child[RIGHT] && sibling->child[RIGHT]->color == BLACK)
				{
					sibling->color = RED;
					parent->color = BLACK;
					break ;
				}
				else if (sibling && sibling->color == BLACK && sibling->child[LEFT] && sibling->child[LEFT]->color == RED && sibling->child[RIGHT] && sibling->child[RIGHT]->color == BLACK && parent->child[LEFT] == (*tmp))
				{
					sibling->color = RED;
					sibling->child[LEFT]->color = BLACK;
					rotateRight(sibling);
				}
				else if (sibling && sibling->color == BLACK && sibling->child[RIGHT] && sibling->child[RIGHT]->color == RED && sibling->child[LEFT] && sibling->child[LEFT]->color == BLACK && parent->child[RIGHT] == (*tmp))
				{
					sibling->color = RED;
					sibling->child[RIGHT]->color = BLACK;
					rotateLeft(sibling);
				}
				else if (sibling && sibling->color == BLACK && sibling->child[RIGHT] && sibling->child[RIGHT]->color == RED && (*tmp) == parent->child[LEFT])
				{
					sibling->color = parent->color;
					parent->color = BLACK;
					rotateLeft(parent);
					break ;
				}
			}
			node->color = BLACK;
		}

		void	getRelatives(pointer & parent, pointer & grandParent, pointer & uncle)
		{
			if (parent)
				grandParent = parent->parent;
			else
				grandParent = _sentinel;
			if (grandParent)
			{
				if (grandParent->child[LEFT] == parent && grandParent->child[RIGHT])
					uncle = grandParent->child[RIGHT];
				else if (grandParent->child[RIGHT] == parent && grandParent->child[LEFT])
					uncle = grandParent->child[LEFT];
				else
					uncle = _sentinel;
			}
			else
				uncle = _sentinel;
		}

		int	hasUncle(pointer & node)
		{
			if (!node->parent)
				return (0);
			if (node->parent->child[LEFT] && node->parent->child[LEFT] == node && node->parent->child[RIGHT])
				return (1);
			if (node->parent->child[RIGHT] && node->parent->child[RIGHT] == node && node->parent->child[LEFT])
				return (1);
			return (0);
		}

		pointer&	getUncle(pointer & node)
		{
			if (node->parent->child[LEFT] == node)
				return (node->parent->child[RIGHT]);
			return (node->parent->child[LEFT]);
		}

		void	balanceInsert(pointer & node)
		{
			pointer*	tmp = &node;
			pointer*	tmp2;
			pointer		parent = node->parent;
			pointer		grandParent;
			pointer		uncle;

			while (1 && *tmp)
			{
				parent = (*tmp)->parent;
				getRelatives(parent, grandParent, uncle);
				if (!parent)
				{
					(*tmp)->color = BLACK;
					break ;
				}
				else if (parent->color == BLACK)
					break ;
				else if (uncle && (*tmp)->color == RED && parent->color == RED && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grandParent->color = RED;
					tmp = &(*tmp)->parent->parent;
				}
				else if ((*tmp)->color == RED && parent->color == RED)
				{
					if (parent->child[RIGHT] == (*tmp) && grandParent->child[LEFT] == parent)
						tmp = rotateLeft(parent);
					else if (parent->child[LEFT] == (*tmp) && grandParent->child[RIGHT] == parent)
						tmp = rotateRight(parent);
					else if (parent->child[LEFT] == (*tmp) && grandParent->child[LEFT] == parent)
					{
						parent->color = BLACK;
						grandParent->color = RED;
						rotateRight(grandParent);
						break ;
					}
					else if (parent->child[RIGHT] == (*tmp) && grandParent->child[RIGHT] == parent)
					{
						parent->color = BLACK;
						grandParent->color = RED;
						rotateLeft(grandParent);
						break ;
					}
				}
				else
					break ;
			}
		}

		void	getRelatives2(pointer & node, pointer & sibling, pointer & leftNephew, pointer & rightNephew)
		{
			if (node->parent->child[LEFT] && node->parent->child[LEFT] == node)
				sibling = node->parent->child[RIGHT];
			else if (node->parent->child[RIGHT])
				sibling = node->parent->child[LEFT];
			else
			{
				sibling = NULL;
				leftNephew = NULL;
				rightNephew = NULL;
			}
			if (sibling && sibling->child[LEFT])
				leftNephew = sibling->child[LEFT];
			else
				leftNephew = NULL;
			if (sibling && sibling->child[RIGHT])
				rightNephew = sibling->child[RIGHT];
			else
				rightNephew = NULL;
		}

		pointer	getSibling(pointer & node)
		{
			if (!node->parent)
				return (NULL);
			if (node->parent->child[LEFT] && node->parent->child[LEFT] == node)
				return (node->parent->child[RIGHT]);
			else if (node->parent->child[RIGHT] && node->parent->child[RIGHT] == node)
				return (node->parent->child[LEFT]);
			return (NULL);
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
				balanceInsert(start);
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

		pointer&	oneChild(pointer& node)
		{
			if (node->child[LEFT] && !node->child[RIGHT])
				return (node->child[LEFT]);
			else if (node->child[RIGHT] && !node->child[LEFT])
				return (node->child[RIGHT]);
			return (NULL);
		}

		void	link(pointer& parent, pointer& oldSon, pointer& node)
		{
			if (parent->child[LEFT] == oldSon)
				parent->child[LEFT] = node;
			else
				parent->child[RIGHT] = node;
			node->parent = parent;
		}

		void	unlink(pointer& parent, pointer& node)
		{
			if (parent->child[LEFT] == node)
				parent->child[LEFT] = _sentinel;
			else
				parent->child[RIGHT] = _sentinel;
			node->parent = _sentinel;
		}
	};
}
