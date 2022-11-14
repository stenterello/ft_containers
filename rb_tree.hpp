/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:53:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/11/14 21:26:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <utility>
#include "utility.hpp"
#include "iterator.hpp"

namespace ft
{
	enum	node_color
	{
		RED = true,
		BLACK = false
	};

	enum	branch
	{
		LEFT,
		RIGHT
	};

	template <class T>
	struct Node
	{
		node_color	color;
		Node*		parent;
		Node*		child[2];
		T			data;

		Node() :
			color(RED),
			parent(NULL),
			data(T())
		{
			child[LEFT] = NULL;
			child[RIGHT] = NULL;
		};
		Node(T value) :
			color(RED),
			parent(NULL),
			data(value)
		{
			child[LEFT] = NULL;
			child[RIGHT] = NULL;
		};
		Node(Node* parentNode, Node* childLeftNode, Node* childRightNode, T value) : 
			color(RED),
			parent(parentNode),
			data(value)
		{
			child[LEFT] = childLeftNode;
			child[RIGHT] = childRightNode;
		};
		Node(Node const & src) :
			color(src.color),
			parent(src.parent),
			data(src.data)
		{
			child[LEFT] = src.child[LEFT];
			child[RIGHT] = src.child[RIGHT];
		};
		Node&	operator=(Node const rhs)
		{
			if (this == &rhs)
				return (*this);
			this->color = rhs.color;
			this->parent = rhs.parent;
			this->child[LEFT] = rhs.child[LEFT];
			this->child[RIGHT] = rhs.child[RIGHT];
			this->data = rhs.data;
		};
		~Node() {};
	};

	template <class Key, class NodeType, class Compare = std::less<Key>>
	class RBTreeSet
	{
		typedef std::allocator<NodeType>					allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef NodeType*									pointer;
		typedef const NodeType*								const_pointer;
		typedef	RBIterator<Key, Compare, NodeType>			iterator;
		typedef RBIterator<const Key, Compare, NodeType>	const_iterator;

		public:

			RBTreeSet() :
				_root(NULL),
				_size(0),
				_alloc(allocator_type()),
				_sentinel(_alloc.allocate(1))
			{
				_alloc.construct(_sentinel, NodeType());
			};

			RBTreeSet(RBTreeSet const & src) :
				_root(src._root),
				_size(src._size),
				_alloc(src._alloc),
				_sentinel(src._sentinel)
			{};

			RBTreeSet&	operator=(RBTreeSet const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_root = rhs._root;
				this->_alloc = rhs._alloc;
				this->_c = rhs._c;
				this->_size = rhs._size;
				this->_sentinel = _alloc.allocate(_size);
				return (*this);
			};

			~RBTreeSet() { _alloc.deallocate(_sentinel, _size); };

			iterator	begin()
			{
				if (!_size)
					return this->end();
				pointer	tmp = _root;
				while (tmp->child[LEFT])
					tmp = tmp->child[LEFT];
				return (iterator(tmp, this->_sentinel));
			}

			const_iterator	begin() const
			{
				if (!_size)
					return this->end();
				pointer	tmp = _root;
				while (tmp->child[LEFT])
					tmp = tmp->child[LEFT];
				return (const_iterator(tmp, this->_sentinel));
			}

			iterator	end()
			{
				this->_sentinel->parent = _root;
				return (iterator(this->_sentinel, this->_sentinel));
			}

			const_iterator end() const
			{
				this->_sentinel->parent = _root;
				return (const_iterator(this->_sentinel, this->_sentinel));
			}
			
			bool		empty() const { return ((!this->_size) ? true : false); }
			size_type	size() const { return this->_size; }
			size_type	max_size() const { return _alloc.max_size(); }

			template <class T2>
			iterator	find(T2 const & k)
			{
				pointer	ret = findPointer(_root, k);
				if (!ret)
					return (this->end());
				return (iterator(ret, _sentinel));
			}

			template <class T2>
			const_iterator	find(T2 const & k) const
			{
				pointer	ret = findPointer(_root, k);
				if (!ret)
					return (this->end());
				return (const_iterator(ret, _sentinel));
			}

			template <class T2>
			pointer	findPointer(pointer start, T2 const & n)
			{
				if (!start)
					return (NULL);
				if (_c(start->data, n))
					return (findPointer(start->child[RIGHT], n));
				else if (!_c(start->data, n))
					return (findPointer(start->child[LEFT], n));
				return (start);
			}

			template <class T2>
			const_pointer	findPointer(pointer start, T2 const & n) const
			{
				if (!start)
					return (NULL);
				if (_c(start, n))
					return (findPointer(start->child[RIGHT], n));
				else if (!_c(start, n))
					return (findPointer(start->child[LEFT], n));
				return (start);
			}

			void	clear()
			{
				this->erase(this->begin(), this->end());
				_size = 0;
			}

			template <class InputIt>
			void	erase(InputIt first, InputIt last)
			{
				
			}

			void	erase(NodeType& node)
			{

			}

			ft::pair<iterator, bool>	insert(Key const & val)
			{
				ft::pair<iterator, bool>	ret;
				pointer						node = _alloc.allocate(1);

				_alloc.construct(node, val);
				node->parent = NULL;
				node->child[LEFT] = NULL;
				node->child[RIGHT] = NULL;
				if (!_size)
				{
					_root = node;
					node->color = BLACK;
					node->child[LEFT] = _sentinel;
					node->child[RIGHT] = _sentinel;
					_size++;
					ret.first = iterator(node, _sentinel);
				}
				else
				{
					
				}
				return (ret);
			}

			pointer	insertNode(pointer& start, pointer& node)
			{
				pointer	tmp;
				if (_c(start->data, node->data))
				{

				}
				else if (_c(node->data, start->data))
				{

				}
				else
					return (start);
				while (tmp)
				{
					if (_c(tmp->data, node->data))
					{}
					else if (_c(node->data, tmp->data))
					{}
					else
						return (tmp);
				}
				return (start);
			}

			void	swap(RBTreeSet& x)
			{
				if (this == &x)
					return ;
				pointer			tmpRoot = _root;
				pointer			tmpSentinel = _sentinel;
				size_type		tmpSize = _size;
				allocator_type	tmpAlloc = _alloc;
				Compare			tmpComp = _c;
				_root = x._root;
				_sentinel = x._sentinel;
				_size = x._size;
				_alloc = x._alloc;
				_c = x._c;
				x._root = tmpRoot;
				x._sentinel = tmpSentinel;
				x._size = tmpSize;
				x._alloc = tmpAlloc;
				x._c = tmpComp;
			}

		private:
			pointer			_root;
			pointer			_sentinel;
			size_type		_size;
			allocator_type	_alloc;
			Compare			_c;
	};
}
