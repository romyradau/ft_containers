#pragma once

#define COUNT 10

#include <iostream>
#include <algorithm>
#include "pair.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"



namespace ft {


	// template <class Type>
	// struct rebind {
	// typedef std::allocator<Type> other;
	// };

	template <typename T >
	struct node {
		typedef T					value_type;
		typedef node<value_type>*	ptr;
		typedef const ptr			const_ptr;
		typedef size_t				size_type;

		value_type					data;
		ptr 						parent;
		ptr 						left;
		ptr 						right;
		ptr							nil;

		node(value_type const & data = value_type()): data(data), parent(NULL), left(NULL), right(NULL), nil(NULL) {}
		// node(value_type const & data, ptr sentimental): data(data), parent(sentimental), left(sentimental), right(sentimental) {}
//to implement the custom null pointer
		node(node<T> const & src): data(src.data), parent(src.parent), left(src.left), right(src.right), nil(src.nil) {}

		node & operator= (node const &rhs){
			if (this != &rhs){
				this->data = rhs.data;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
				this->nil = rhs.nil;
			}
			return *this;
		}
		~node(){}


		// find the node with the minimum key
		ptr min_node(ptr curr) {
			while (curr->left != curr->nil) {
				curr = curr->left;
			}
			return (curr);
		}

		// find the node with the maximum key
		ptr max_node(ptr curr) {
			while (curr->right != curr->nil) {

				curr = curr->right;
			}
			return (curr);
		}

		ptr successor(ptr curr) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (curr->right != curr->nil) {
			return min_node(curr->right);
		}

		// else it is the lowest ancestor of curr whose
		// left child is also an ancestor of curr.
		ptr par = curr->parent;
		while (par != par->nil && curr == par->right) {

			curr = par;
			par = par->parent;
		}
		return par;
		}
	// find the predecessor of a given node
		ptr predecessor(ptr curr) {
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the 
			// left subtree
		if (curr->left != curr->nil) {
			return max_node(curr->left);
		}

		ptr y = curr->parent;
		while (y != y->nil && curr == y->left) {

			curr = y;
			y = y->parent;
		}

		return y;
	}
	};


template<
	class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> > >

	class avl_tree {
	public:
		/*
		** ----------------------- MEMBER TYPES -----------------------
		*/
		typedef Key														key_type;
		typedef T														mapped_type;
		typedef	ft::pair<const Key, T> 									value_type;
		typedef	Compare													key_compare; //https://en.cppreference.com/w/cpp/utility/functional/less
		typedef	Allocator												allocator_type;
		typedef ft::node<value_type>									node;
		typedef typename node::ptr										node_pointer;
		typedef typename node::const_ptr								const_node_pointer;
		typedef typename allocator_type::template rebind<node>::other	node_allocator_type;
		typedef	std::size_t												size_type;
		// typedef	ft::map_iterator<value_type>							iterator;
		typedef	ft::map_iterator<value_type>							iterator;
		typedef	ft::map_iterator<const value_type>						const_iterator;
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		// typedef	ft::avl_tree<key_type, mapped_type, value_type, allocator_type>	avl;


		node_pointer 													_root;
		node_pointer													_sentimental;
		key_compare														_compare;//nicht dafuer da um etwas reinzuspeichern										
		size_type														_size;
		allocator_type													_pair_alloc;
		node_allocator_type												_node_alloc;
			//beim allocator den template type asugewechselt
			//other ist ein allocator auf diesen type
	private:

		void	be_sentimental(){
			_sentimental = _node_alloc.allocate(1);
			_pair_alloc.construct(&(_sentimental->data), value_type()); //wohin und was
			_sentimental->parent = _sentimental;
			_sentimental->left = _sentimental;
			_sentimental->right = _sentimental;
			_sentimental->nil = _sentimental;
		}
	
	public:
		avl_tree(): _compare(), _size(0), _pair_alloc(), _node_alloc() {
			be_sentimental();
			_root = _sentimental;

		}
		avl_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), const allocator_type& nalloc = node_allocator_type()): _compare(comp), _size(0), _pair_alloc(alloc), _node_alloc(nalloc){
			be_sentimental();
			_root = _sentimental;
		}

		avl_tree(avl_tree const &other): _compare(other._compare), _size(other._size), _pair_alloc(other._pair_alloc), _node_alloc(other._node_alloc){
			be_sentimental();
			_root = _sentimental;
			// for (const_iterator it = other.begin(); it != other.end(); ++it)
			// 	insert(*it);
		}

		avl_tree & operator=(avl_tree const &rhs){
			if (this != &rhs) {
				clear();
				_compare = rhs._compare;
				_pair_alloc = rhs._pair_alloc;
				_node_alloc = rhs._node_alloc;
				// for (const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
				// 	insert(*it);
				// }
			}
				return *this;
		}

		~avl_tree(){
			clear();
			this->_pair_alloc.destroy(&(this->_sentimental->data));
			this->_node_alloc.deallocate(this->_sentimental, 1);
		}//muss man hier deallocaten?

		node_pointer getRoot() const { return (this->_root); }

		int getBalanceFactor(node_pointer curr) const {
			int rightHeight = curr ? getHeight(curr->right) : 0;
			int leftHeight = curr ? getHeight(curr->left) : 0;
			return (rightHeight - leftHeight);
		}

		int getHeight(node_pointer curr) const {
			if (curr == this->_sentimental)
				return (0);
			return ( 1 + std::max( getHeight(curr->right), getHeight(curr->left) ) );
		}

		void leftRotate(node_pointer x) {
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != this->_sentimental) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == this->_sentimental) {
				this->_root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		} 

		void rightRotate(node_pointer x) {
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != this->_sentimental) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == this->_sentimental) {
				this->_root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}
		// find the node with the minimum key
		static node_pointer min_node(node_pointer curr) {
			while (curr->left != curr->nil) {

				curr = curr->left;
			}
			return (curr);
		}

		// find the node with the maximum key
		static node_pointer max_node(node_pointer curr) {
			while (curr->right != curr->nil) {

				curr = curr->right;
			}
			return (curr);
		}

	static node_pointer successor(node_pointer curr) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (curr->right != curr->nil) {
			return min_node(curr->right);
		}

		// else it is the lowest ancestor of curr whose
		// left child is also an ancestor of curr.
		node_pointer par = curr->parent;
		while (par != par->nil && curr == par->right) {

			curr = par;
			par = par->parent;
		}
		return par;
	}

	// find the predecessor of a given node
	static node_pointer predecessor(node_pointer x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != x->nil) {
			return max_node(x->left);
		}

		node_pointer y = x->parent;
		while (y != y->nil && x == y->left) {

			x = y;
			y = y->parent;
		}

		return y;
	}
		void rebalance(node_pointer curr) {
			if (getBalanceFactor(curr) > 0) {
				if (getBalanceFactor(curr->right) < 0) {
					rightRotate(curr->right);
					leftRotate(curr);
				} else
					leftRotate(curr);
			} 
			else if (getBalanceFactor(curr) < 0) {
				if (getBalanceFactor(curr->left) > 0) {
					leftRotate(curr->left);
					rightRotate(curr);
				} else
					rightRotate(curr);
			}
		}

		void updateBalance(node_pointer curr) {
			if (getBalanceFactor(curr) < -1 || getBalanceFactor(curr) > 1) {
				this->rebalance(curr);
			}
			if (curr->parent != this->_sentimental)//realy double neccesssary?
				updateBalance(curr->parent);
		}

		void copyData(node_pointer dest, node_pointer src) {
			this->_pair_alloc.destroy(&(dest->data));
			this->_pair_alloc.construct(&(dest->data), src->data);
		}

		ft::pair<iterator,bool> insert(value_type key) {

			node_pointer curr = search(key);

			if (curr && curr != this->_sentimental){
				iterator res(curr);
				return (ft::make_pair<iterator, bool>(res, false));
			}

			// PART 1: Ordinary BST insert
			curr = this->_node_alloc.allocate(1);
			this->_pair_alloc.construct(&curr->data, value_type(key));//calls constructor of value_type
			curr->parent = this->_sentimental;
			curr->left = this->_sentimental;
			curr->right = this->_sentimental;
			curr->nil = this->_sentimental;

			node_pointer y = this->_sentimental;
			node_pointer x = this->_root;

			while (x != this->_sentimental) {

				y = x;
				if (this->_compare(curr->data, x->data))//damit nur das erste verglichen wird
					x = x->left;
				else
					x = x->right;
			}

			// y is parent of x
			curr->parent = y;
			if (y == this->_sentimental)
				this->_root = curr;
			else if (this->_compare(curr->data,y->data))
				y->left = curr;
			else
				y->right = curr;

			// PART 2: re-balance the node if necessary
			this->updateBalance(curr);
			this->_size++;
			this->_sentimental->parent = max_node(this->_root);
			iterator res(curr);
			return (ft::make_pair<iterator, bool>(res, true));
		}



		node_pointer searchHelper(node_pointer curr, value_type& key) const {
			while (curr && curr != this->_sentimental) {

				if (this->_compare(key, curr->data))
					curr = curr->left;
				else if (this->_compare(curr->data, key))
					curr = curr->right;
				else
					break;
			}
			return (curr);
		}
		
		node_pointer searchKey(node_pointer curr, key_type const & key) const {
			while (curr != this->_sentimental) {

				if (this->_compare(key, curr->data))
					curr = curr->left;
				else if (this->_compare(curr->data, key))
					curr = curr->right;
				else
					break;
			}
			return (curr);
		}
		//vielleicht ohne den overload


		node_pointer search(value_type key) const {
			return (searchHelper(this->_root, key));
		}

		void removeChild(node_pointer& parent, node_pointer& child) {
			if (parent->left == child)
				parent->left = this->_sentimental;
			else if (parent->right == child)
				parent->right = this->_sentimental;
		}

		void destroynode(node_pointer curr) {

			if (curr != this->_sentimental) {//inconsistent
				this->_pair_alloc.destroy(&curr->data);
				this->_node_alloc.deallocate(curr, 1);
			}
		}

		node_pointer deletenodeHelper(node_pointer curr, value_type key) {
			curr = searchHelper(curr, key);
			if (curr == this->_sentimental) return (curr);

			node_pointer prev = curr->parent;

			// case 1: leaf node
			if (curr->left == this->_sentimental && curr->right == this->_sentimental) {
				if (prev != this->_sentimental) {
					removeChild(prev, curr);
				}
				else 
					this->_root = this->_sentimental;
			}
			
			// case 2: node has one child
			else if (curr->right == this->_sentimental) {
				node_pointer tmp = curr->left;
				copyData(curr, tmp);
				curr->left = this->_sentimental;
				curr = tmp;
			}
			else if (curr->left == this->_sentimental) {
				node_pointer tmp = curr->right;
				copyData(curr, tmp);
				curr->right = this->_sentimental;
				curr = tmp;
			}

			// case 3: node has two children
			else {
				node_pointer tmp = min_node(curr->right);
				copyData(curr, tmp);
				curr = deletenodeHelper(curr->right, curr->data);
			}

			return (curr);
		}

		void deletenode (value_type key) {
			node_pointer deletedNode = deletenodeHelper(this->_root, key);
			if (deletedNode != this->_sentimental) {
				if (deletedNode->parent != this->_sentimental)
					updateBalance(deletedNode->parent);
				else if (this->_root != this->_sentimental)
					updateBalance(this->_root);
				this->destroynode(deletedNode);
				// this->_pair_alloc.destroy(&deletedNode->data);
				// this->_node_alloc.deallocate(deletedNode, 1);
				this->_size--;
			}
		}

		void clearHelper(node_pointer curr) {
			if (curr == this->_sentimental)
				return ;
			clearHelper(curr->right);
			clearHelper(curr->left);
			destroynode(curr);
		}

		void clear() {
			clearHelper(this->_root);
			this->_size = 0;
			this->_root = this->_sentimental;
		}

		size_type size() const{
			return this->_size;
		}
		
		// template <class T>
		// void helper_swap( T& a, T& b ){
	  	// 	T c(a);
	  	// 	a=b;
	  	// 	b=c;
		// }
		void	swap(avl_tree & other) {
			ft::swap(_root, other._root);
			ft::swap(_size, other._size);
			ft::swap(_compare, other._compare);
			ft::swap(_pair_alloc, other._pair_alloc);
			ft::swap(_node_alloc, other._node_alloc);
			//was fehlt bei unserem  heir noch?

			// if (_root)
			// _root->parent = &_end;
			// if (other._root)
			// 	other._root->parent = &other._end;
		}

		// template <typename Key>
		// iterator lower_bound(const Key& key)
		// {
		// 	iterator it = begin();
		// 	while (_compare(*it, key) && it != end())
		// 		++it;
		// 	return iterator(it);	
		// }

		// template <typename Key>
		// const_iterator lower_bound(const Key& key) const
		// {
		// 	const_iterator it = begin();
		// 	while (_compare(*it, key) && it != end())
		// 		++it;
		// 	return const_iterator(it);
		// }

		// template <typename Key>
		// iterator upper_bound(const Key& key)
		// {
		// 	iterator it = lower_bound(key);
		// 	if (!_compare(*it, key) && !_compare(key, *it))
		// 		++it;
		// 	return it;
		// }

		// template <typename Key>
		// const_iterator upper_bound(const Key& key) const
		// {
		// 	const_iterator it = lower_bound(key);
		// 	if(!_compare(*it, key) && !_compare(key, *it))
		// 		++it;
		// 	return it;
		// }

		// template <typename Key>
		// ft::pair<iterator,iterator> equal_range(const Key& key)
		// {return ft::make_pair(lower_bound(key), upper_bound(key)); }

		// template <typename Key>
		// ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		// {return ft::make_pair(lower_bound(key), upper_bound(key)); }

		void print2D(node_pointer curr, int space, std::string dir) const {
			// Base case
			if (curr == this->_sentimental)
				return ;

			// Increase distance between levels
			space += COUNT;

			// Process right child first
			print2D(curr->right, space, "v ");

			// Print current node after space
			// count
			std::cout << std::endl;
			for (int i = COUNT; i < space; i++)
				std::cout << " ";
			std::cout << dir << curr->data << " (BF: " << getBalanceFactor(curr) << ", H: " << getHeight(curr) << ") " << std::endl;

			// Process left child
			print2D(curr->left, space, "^ ");
		}

	public:
		void printTree() const {
			this->print2D(this->_root, 0, "");
		}
	};
}