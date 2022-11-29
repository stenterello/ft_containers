/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:53:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/29 01:56:56 by ddelladi         ###   ########.fr       */
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
		RED,
		BLACK,
		SENTINEL
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
		typedef std::allocator<NodeType>						allocator_type;
		typedef typename allocator_type::size_type				size_type;
		typedef NodeType*										pointer;
		typedef const NodeType*									const_pointer;
		typedef RBIterator<Key, Compare, NodeType>				iterator;
		typedef RBIterator<const Key, Compare, NodeType>		const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		RBTreeSet() :	_root(NULL),
						_size(0),
						_alloc(allocator_type())
		{
			_sentinel = _alloc.allocate(1);
			_sentinel->color = SENTINEL;
			_root = _sentinel;
			_sentinel->parent = _root;
			_sentinel->data = 1;
		};

		RBTreeSet(RBTreeSet const &src)
		{
			_alloc = allocator_type();
			_sentinel = _alloc.allocate(1);
			_sentinel->color = SENTINEL;
			_root = _sentinel;
			_sentinel->parent = _root;
			_sentinel->data = 1;
			_root = _sentinel;
			_size = 0;
			iterator	iter = src.begin();
			while (iter != src.end())
				this->insert(*iter++);
		};

		RBTreeSet &operator=(RBTreeSet const &rhs)
		{
			if (this == &rhs)
				return (*this);
			_alloc = rhs.get_allocator();
			_sentinel = _alloc.allocate(1);
			_sentinel->color = SENTINEL;
			_root = _sentinel;
			_sentinel->parent = _root;
			_sentinel->data = 1;
			_root = _sentinel;
			_size = 0;
			iterator	iter = rhs.begin();
			while (iter != rhs.end())
				this->insert(*iter++);
			return (*this);
		};

		~RBTreeSet()
		{
			this->clear();
			_alloc.deallocate(_sentinel, 1);
		};

		allocator_type	get_allocator() const { return (this->_alloc); }

		bool empty() const { return ((!this->_size) ? true : false); }
		size_type size() const { return this->_size; }
		size_type max_size() const { return _alloc.max_size(); }

		size_type	count(Key const & k) const
		{
			iterator	ret = this->find(k);
			if (ret == iterator(_sentinel, _sentinel))
				return (0);
			return (1);
		}

		iterator				begin() { return (iterator(min(), _sentinel)); }
		const_iterator			begin() const { return (const_iterator(min(), _sentinel)); }
		iterator				end() { return (_sentinel); }
		const_iterator			end() const { return (_sentinel); }
		reverse_iterator		rbegin() { return (iterator(max(), _sentinel)); }
		const_reverse_iterator	rbegin() const { return (const_iterator(max(), _sentinel)); }
		reverse_iterator		rend() { return (_sentinel); }
		const_reverse_iterator	rend() const { return (_sentinel); }

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
			pointer node = _alloc.allocate(1);

			node->color = RED;
			node->parent = _sentinel;
			node->child[LEFT] = _sentinel;
			node->child[RIGHT] = _sentinel;
			node->data = val;

			if (!_size)
			{
				_root = node;
				_sentinel->parent = node;
				node->color = BLACK;
				_size++;
				ret.first = iterator(node, _sentinel);
				ret.second = true;
				return (ret);
			}
			else
			{
				ret.first = iterator(node, _sentinel);
				ret.second = false;
				if (_c(val, _root->data))
					return (insertNode(_root->child[LEFT], node, _root, 1));
				else if (_c(_root->data, val))
					return (insertNode(_root->child[RIGHT], node, _root, 1));
				else
				{
					_alloc.deallocate(node, 1);
					return (ret);
				}
			}
		}

		iterator	find(Key const & val) const
		{
			pointer	node = _root;

			if (node && node != _sentinel)
				return (findPointer(node, val));
			return (iterator(_sentinel, _sentinel));
		}

		iterator	findPointer(pointer& start, Key const & val) const
		{
			if (!start || start->color == SENTINEL)
				return (iterator(_sentinel, _sentinel));
			if (_c(val, start->data))
				return (findPointer(start->child[LEFT], val));
			else if (_c(start->data, val))
				return (findPointer(start->child[RIGHT], val));
			else
				return (iterator(start, _sentinel));
		}

		pointer	getPredecessor(pointer const & node) const
		{
			pointer	tmp = node;
			
			if (node == min())
				return (_sentinel);
			if (tmp->child[LEFT] != _sentinel)
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

		pointer	getSuccessor(pointer const & node) const
		{
			pointer	tmp = node;
			
			if (node == max())
				return (_sentinel);
			if (tmp->child[RIGHT] != _sentinel)
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
			const pointer*	node = &_root;

			if (!(*node) || (*node) == _sentinel)
				return (_sentinel);

			while ((*node)->child[LEFT] && (*node)->child[LEFT] != _sentinel)
				node = &(*node)->child[LEFT];
			return (*node);
		}

		pointer	min(pointer const & node) const
		{
			const pointer*	tmp = &node;

			if (!(*tmp) || (*tmp) == _sentinel)
				return (_sentinel);

			while ((*tmp)->child[LEFT] && (*tmp)->child[LEFT] != _sentinel)
				tmp = &(*tmp)->child[LEFT];
			return (*tmp);
		}
		
		pointer	max() const
		{
			pointer	node = _root;

			if (!node || node == _sentinel)
				return (_sentinel);

			while (node->child[RIGHT] && node->child[RIGHT] != _sentinel)
				node = node->child[RIGHT];
			return (node);
		}

		pointer	max(pointer const & node) const
		{
			pointer	tmp = node;

			if (!node || node == _sentinel)
				return (_sentinel);

			while (tmp->child[RIGHT] != _sentinel)
				tmp = tmp->child[RIGHT];
			return (tmp);
		}

		iterator	erase(iterator pos)
		{
			iterator	ret = getSuccessor(pos.node);

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
			if (this->erase_deep(key) != this->end())
				return (1);
			return (0);
		}

		iterator	erase_deep(Key const & val)
		{
			pointer		node = find(val).node;
			pointer		tmp;
			pointer		successor;
			pointer		toHandle;
			iterator	ret;
			
			if (!node)
				return (iterator(_sentinel, _sentinel));
			else if (node != _sentinel)
				ret = this->find(getSuccessor(node)->data);
			else
				return (iterator(_sentinel, _sentinel));

			if ((!node->child[LEFT] && !node->child[RIGHT]) || (node->child[LEFT] == _sentinel && node->child[RIGHT] == _sentinel))
			{
				tmp = node->parent;
				if (node->color == BLACK && node != _root)
					balanceDelete(node);
				if (tmp != _sentinel)
					unlink(tmp, node);
				else
				{
					_root = _sentinel;
					_sentinel->parent = _root;
				}
			}
			else if (oneChild(node) != _sentinel)
			{
				if (node->color == BLACK && node != _root)
					balanceDelete(node);
				oneChild(node)->parent = node->parent;
				if (node != _root)
					link(node->parent, node, oneChild(node));
				else
				{
					_root = oneChild(node);
					_sentinel->parent = _root;
				}
			}
			else
			{
				toHandle = NULL;
				if (_c(node->data, _root->data))
					successor = getSuccessor(node);
				else
					successor = getPredecessor(node);
				balanceDelete(successor);
				if (successor->child[RIGHT] != _sentinel)
				{
					toHandle = successor->child[RIGHT];
					successor->child[RIGHT] = _sentinel;
				}
				unlink(successor->parent, successor);
				link(node->parent, node, successor);
				if (node->child[LEFT] != _sentinel)
				{
					node->child[LEFT]->parent = successor;
					successor->child[LEFT] = node->child[LEFT];
				}
				if (node->child[RIGHT] != _sentinel)
				{
					if (successor->child[RIGHT] != _sentinel)
						link(successor->parent, successor, successor->child[RIGHT]);
					node->child[RIGHT]->parent = successor;
					successor->child[RIGHT] = node->child[RIGHT];
				}
			}
			_alloc.deallocate(node, 1);
			node = NULL;
			_size--;
			return (ret);
		}

		void	clear()
		{
			iterator	iter = this->begin();
			iterator	end = this->end();

			while (iter != end)
				erase(*iter++);
		}

		iterator	lower_bound(Key const & k)
		{
			iterator	ret = this->begin();

			while (ret != this->end())
			{
				if (!_c(ret.node->data, k))
					break ;
				ret++;
			}
			return (ret);
		}

		const_iterator	lower_bound(Key const & k) const
		{
			const_iterator	ret = this->begin();

			while (ret != this->end())
			{
				if (!_c(ret.node->data, k))
					break ;
				ret++;
			}
			return (ret);
		}

		iterator	upper_bound(Key const & k)
		{
			iterator	ret = this->begin();

			while (ret != this->end())
			{
				if (_c(k, ret.node->data))
					break ;
				ret++;
			}
			return (ret);
		}

		const_iterator	upper_bound(Key const & k) const
		{
			const_iterator	ret = this->begin();

			while (ret != this->end())
			{
				if (_c(k, ret.node->data))
					break ;
				ret++;
			}
			return (ret);
		}

		ft::pair<iterator, iterator>				equal_range(const Key& key)
		{
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
		{
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}

		void			swap(RBTreeSet & rhs)
		{
			if (this == &rhs)
				return ;
			
			pointer			tmpRoot = this->_root;
			pointer			tmpSentinel = this->_sentinel;
			size_type		tmpSize = this->_size;
			allocator_type	tmpAllocatorType = this->_alloc;
			Compare			tmpCompare = this->_c;

			this->_root = rhs._root;
			this->_sentinel = rhs._sentinel;
			this->_size = rhs._size;
			this->_alloc = rhs._alloc;
			this->_c = rhs._c;

			rhs._root = tmpRoot;
			rhs._sentinel = tmpSentinel;
			rhs._size = tmpSize;
			rhs._alloc = tmpAllocatorType;
			rhs._c = tmpCompare;
		}

	protected:
		pointer			_root;
		pointer			_sentinel;
		size_type		_size;
		allocator_type	_alloc;
		Compare			_c;

		pointer	getOnlyChildWithoutChildren(pointer const & node)
		{
			pointer	child;

			if (node->child[LEFT] != _sentinel && node->child[RIGHT] == _sentinel)
				child = node->child[LEFT];
			else if (node->child[LEFT] == _sentinel && node->child[RIGHT] != _sentinel)
				child = node->child[RIGHT];
			else
				return (NULL);
			if (child->child[LEFT] != _sentinel || child->child[RIGHT] != _sentinel)
				return (NULL);
			return (child);
		}

		pointer*	rotateLeft(pointer & node)
		{
			pointer		toHandle;
			pointer*	tmp = &node;

			if ((*tmp)->child[RIGHT]->child[LEFT] != _sentinel)
				toHandle = (*tmp)->child[RIGHT]->child[LEFT];
			else
				toHandle = NULL;
			if ((*tmp) == _root)
			{
				_root = (*tmp)->child[RIGHT];
				_sentinel->parent = _root;
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
			(*tmp)->child[RIGHT] = _sentinel;
			if (toHandle)
				insertNode((*tmp)->parent, toHandle, (*tmp)->parent, 0);
			return (&node);
		}

		pointer*	rotateRight(pointer & node)
		{
			pointer		toHandle;
			pointer*	tmp = &node;
			pointer*	ret;

			if ((*tmp) && (*tmp)->child[LEFT] != _sentinel && (*tmp)->child[LEFT]->child[RIGHT] != _sentinel)
				toHandle = (*tmp)->child[LEFT]->child[RIGHT];
			else
				toHandle = NULL;
			if ((*tmp) == _root)
			{
				_root = (*tmp)->child[LEFT];
				_sentinel->parent = _root;
				(*tmp)->child[LEFT]->parent = _sentinel;
			}
			else
			{
				(*tmp)->child[LEFT]->parent = (*tmp)->parent;
				if ((*tmp)->parent->child[RIGHT] == *tmp)
					(*tmp)->parent->child[RIGHT] = (*tmp)->child[LEFT];
				else
					(*tmp)->parent->child[LEFT] = (*tmp)->child[LEFT];
			}
			(*tmp)->parent = (*tmp)->child[LEFT];
			(*tmp)->child[LEFT]->child[RIGHT] = (*tmp);
			(*tmp)->child[LEFT] = _sentinel;
			if (toHandle)
				insertNode((*tmp), toHandle, (*tmp), 0);
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
				if ((*tmp) == (*tmp)->parent->child[LEFT])
				{
					if (sibling && sibling->color == RED)
					{
						(*tmp)->parent->color = RED;
						sibling->color = BLACK;
						rotateLeft((*tmp)->parent);
					}
					else
					{
						if (leftNephew && leftNephew->color == BLACK && rightNephew && rightNephew->color == BLACK)
						{
							sibling->color = RED;
							tmp = &(*tmp)->parent;
						}
						else if (leftNephew && leftNephew->color == RED && rightNephew && rightNephew->color == BLACK)
						{
							leftNephew->color = BLACK;
							sibling->color = RED;
							rotateRight(sibling);
						}
						else if (rightNephew && rightNephew->color == RED)
						{
							sibling->color = (*tmp)->parent->color;
							(*tmp)->parent->color = BLACK;
							rightNephew->color = BLACK;
							rotateLeft((*tmp)->parent);
							break ;
						}
						else if (oneChild(*tmp) && oneChild(*tmp)->color == RED)
						{
							oneChild(*tmp)->color = BLACK;
							break ;
						}
						else if (sibling && sibling->color == BLACK && (*tmp)->color == BLACK)
						{
							sibling->color = RED;
							tmp = &(*tmp)->parent;
						}
					}
				}
				else
				{
					if (sibling && sibling->color == RED)
					{
						(*tmp)->parent->color = RED;
						sibling->color = BLACK;
						rotateRight((*tmp)->parent);
					}
					else
					{
						if (rightNephew && rightNephew->color == BLACK && leftNephew&& leftNephew->color == BLACK)
						{
							sibling->color = RED;
							tmp = &(*tmp)->parent;
						}
						else if (rightNephew && rightNephew->color == RED && leftNephew && leftNephew->color == BLACK)
						{
							rightNephew->color = BLACK;
							sibling->color = RED;
							rotateLeft(sibling);
						}
						else if (leftNephew && leftNephew->color == RED)
						{
							sibling->color = (*tmp)->parent->color;
							(*tmp)->parent->color = BLACK;
							leftNephew->color = BLACK;
							rotateRight((*tmp)->parent);
							break ;
						}
						else if (oneChild(*tmp)->color == RED)
						{
							oneChild(*tmp)->color = BLACK;
							break ;
						}
						else if (sibling && sibling->color == BLACK && (*tmp)->color == BLACK)
						{
							sibling->color = RED;
							tmp = &(*tmp)->parent;
						}
					}
				}
			}
		}

		void	getRelatives(pointer & parent, pointer & grandParent, pointer & uncle)
		{
			if (parent != _sentinel)
				grandParent = parent->parent;
			else
				grandParent = NULL;
			if (grandParent != _sentinel && grandParent)
			{
				if (grandParent->child[LEFT] == parent && grandParent->child[RIGHT] != _sentinel)
					uncle = grandParent->child[RIGHT];
				else if (grandParent->child[RIGHT] == parent && grandParent->child[LEFT] != _sentinel)
					uncle = grandParent->child[LEFT];
				else
					uncle = NULL;
			}
			else
				uncle = NULL;
		}

		int	hasUncle(pointer & node)
		{
			if (node->parent == _sentinel)
				return (0);
			if (node->parent->child[LEFT] != _sentinel && node->parent->child[LEFT] == node && node->parent->child[RIGHT] != _sentinel)
				return (1);
			if (node->parent->child[RIGHT] != _sentinel && node->parent->child[RIGHT] == node && node->parent->child[LEFT] != _sentinel)
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
			pointer		parent = node->parent;
			pointer		grandParent;
			pointer		uncle;

			while (1 && *tmp && *tmp != _sentinel)
			{
				parent = (*tmp)->parent;
				getRelatives(parent, grandParent, uncle);
				if (!parent || parent == _sentinel)
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
			if (node->parent->child[LEFT] != _sentinel && node->parent->child[LEFT] == node)
				sibling = node->parent->child[RIGHT];
			else if (node->parent->child[RIGHT] != _sentinel)
				sibling = node->parent->child[LEFT];
			else
			{
				sibling = NULL;
				leftNephew = NULL;
				rightNephew = NULL;
			}
			if (sibling && sibling->child[LEFT] != _sentinel)
				leftNephew = sibling->child[LEFT];
			else
				leftNephew = NULL;
			if (sibling && sibling->child[RIGHT] != _sentinel)
				rightNephew = sibling->child[RIGHT];
			else
				rightNephew = NULL;
		}

		pointer	getSibling(pointer & node)
		{
			if (node->parent == _sentinel)
				return (NULL);
			if (node->parent->child[LEFT] != _sentinel && node->parent->child[LEFT] == node)
				return (node->parent->child[RIGHT]);
			else if (node->parent->child[RIGHT] != _sentinel && node->parent->child[RIGHT] == node)
				return (node->parent->child[LEFT]);
			return (NULL);
		}

		ft::pair<iterator, bool> insertNode(pointer &start, pointer &node, pointer& parent, int flag)
		{
			ft::pair<iterator, bool>	ret;
			
			if (!start || start == _sentinel)
			{
				node->parent = parent;
				if (_c(node->data, parent->data))
					parent->child[LEFT] = node;
				else
					parent->child[RIGHT] = node;
				start = node;
				if (flag)
					_size++;
				balanceInsert(start);
				ret.first = iterator(start, _sentinel);
				ret.second = true;
				return (ret);
			}
			if (_c(node->data, start->data))
				return (insertNode(start->child[LEFT], node, start, flag));
			else if (_c(start->data, node->data))
				return (insertNode(start->child[RIGHT], node, start, flag));
			ret.first = iterator(node, _sentinel);
			delete node;
			ret.second = false;
			return (ret);
		}

		pointer&	oneChild(pointer& node)
		{
			if (node->child[LEFT] != _sentinel && node->child[RIGHT] == _sentinel)
				return (node->child[LEFT]);
			else if (node->child[RIGHT] != _sentinel && node->child[LEFT] == _sentinel)
				return (node->child[RIGHT]);
			return (_sentinel);
		}

		void	link(pointer& parent, pointer& oldSon, pointer& node)
		{
			if (parent->child[LEFT] == oldSon)
				parent->child[LEFT] = node;
			else
				parent->child[RIGHT] = node;
			if (node != _sentinel)
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
