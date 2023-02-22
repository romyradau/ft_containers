#pragma once

#define COUNT 10

#include <iostream>
#include <algorithm>
#include "pair.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"



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

		node(value_type const & data = value_type()): data(data), parent(NULL), left(NULL), right(NULL) {}
		node(node<T> const & src): data(src.data), parent(src.parent), left(src.left), right(src.right) {}
		node & operator= (node const &rhs){
			if (this != &rhs){
				this->data = rhs.data;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
			return *this;
		}
		~node(){}


		// find the node with the minimum key
		ptr min_node(ptr curr) {
			while (curr->left != NULL) {
				curr = curr->left;
			}
			return (curr);
		}

		// find the node with the maximum key
		ptr max_node(ptr curr) {
			while (curr->right != NULL) {
				curr = curr->right;
			}
			return (curr);
		}

		ptr successor(ptr curr) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (curr->right != NULL) {
			return min_node(curr->right);
		}

		// else it is the lowest ancestor of curr whose
		// left child is also an ancestor of curr.
		ptr par = curr->parent;
		while (par != NULL && curr == par->right) {
			curr = par;
			par = par->parent;
		}
		return par;
		}
	// find the predecessor of a given node
		ptr predecessor(ptr x) {
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the 
			// left subtree
			if (x->left != NULL) {
				return max_node(x->left);
			}

			// int&	getBalance(void){return this->bf;}

			};
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


	private:
		node_pointer 													_root;
		key_compare														_compare;//nicht dafuer da um etwas reinzuspeichern										
		size_type														_size;
		allocator_type													_pair_alloc;
		node_allocator_type												_node_alloc;
			//beim allocator den template type asugewechselt
			//other ist ein allocator auf diesen type
	
	public:
		avl_tree(): _root(NULL), _compare(), _size(0), _pair_alloc(), _node_alloc() {}
		avl_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), const allocator_type& nalloc = node_allocator_type()): _root(NULL), _compare(comp), _size(0), _pair_alloc(alloc), _node_alloc(nalloc){}
		//TODO:ausarbeitung missing!
		avl_tree(avl_tree const &other): _root(other._root), _compare(other._compare), _size(other._size), _pair_alloc(other._pair_alloc), _node_alloc(other._node_alloc){}//hier alles allocaten
		avl_tree & operator=(avl_tree const &rhs){}//hier alles allocaten
		~avl_tree(){}

		node_pointer getRoot() const { return (this->_root); }

		int getBalanceFactor(node_pointer curr) const {
			int rightHeight = curr ? getHeight(curr->right) : 0;
			int leftHeight = curr ? getHeight(curr->left) : 0;
			return (rightHeight - leftHeight);
		}

		int getHeight(node_pointer curr) const {
			if (curr == NULL)
				return (0);
			return ( 1 + std::max( getHeight(curr->right), getHeight(curr->left) ) );
		}

		void leftRotate(node_pointer x) {
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != NULL) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
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
			if (y->right != NULL) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				this->_root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}


	static node_pointer successor(node_pointer curr) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (curr->right != NULL) {
			return min_node(curr->right);
		}

		// else it is the lowest ancestor of curr whose
		// left child is also an ancestor of curr.
		node_pointer par = curr->parent;
		while (par != NULL && curr == par->right) {
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
		if (x->left != NULL) {
			return max_node(x->left);
		}

		node_pointer y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}
		void rebalance(node_pointer curr) {
			if (getBalanceFactor(curr) > 0) {
				if (getBalanceFactor(curr->right) < 0) {
					std::cout << "right left rotate" << std::endl;
					rightRotate(curr->right);
					leftRotate(curr);
				} else {
					std::cout << "left rotate" << std::endl;
					leftRotate(curr);
				}
			} 
			else if (getBalanceFactor(curr) < 0) {
				if (getBalanceFactor(curr->left) > 0) {
					std::cout << "left right rotate" << std::endl;
					leftRotate(curr->left);
					rightRotate(curr);
				} else {
					std::cout << "right rotate" << std::endl;
					rightRotate(curr);
				}
			}
		}

		void updateBalance(node_pointer curr) {
			if (getBalanceFactor(curr) < -1 || getBalanceFactor(curr) > 1) {
				std::cout << "Rebalancing needed." << std::endl;
				this->rebalance(curr);
			}
			if (curr->parent != NULL)
				updateBalance(curr->parent);
		}

		ft::pair<iterator,bool> insert(value_type key) {

			node_pointer curr = search(key);

			if (curr){
				iterator res(curr);
				return (ft::make_pair<iterator, bool>(res, false));
			}

			// PART 1: Ordinary BST insert
			curr = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(curr, node(key));

			node_pointer y = NULL;
			node_pointer x = this->_root;

			while (x != NULL) {
				y = x;
				if (this->_compare(curr->data, x->data))//damit nur das erste verglichen wird
					x = x->left;
				else
					x = x->right;
			}

			// y is parent of x
			curr->parent = y;
			if (y == NULL)
				this->_root = curr;
			else if (this->_compare(curr->data,y->data))
				y->left = curr;
			else
				y->right = curr;

			// PART 2: re-balance the node if necessary
			this->updateBalance(curr);
			this->_size++;
			iterator res(curr);
			return (ft::make_pair<iterator, bool>(res, true));
		}

		// find the node with the minimum key
		static node_pointer min_node(node_pointer curr) {
			while (curr->left != NULL) {
				curr = curr->left;
			}
			return (curr);
		}

		// find the node with the maximum key
		static node_pointer max_node(node_pointer curr) {
			while (curr->right != NULL) {
				curr = curr->right;
			}
			return (curr);
		}

		node_pointer searchHelper(node_pointer curr, value_type& key) const {
			while (curr) {
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
			while (curr) {
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
				parent->left = NULL;
			else if (parent->right == child)
				parent->right = NULL;
		}

		node_pointer deletenodeHelper(node_pointer curr, value_type key) {
			curr = searchHelper(curr, key);
			if (!curr) return (NULL);

			node_pointer prev = curr->parent;

			// case 1: leaf node
			if (!curr->left && !curr->right) {
				if (prev) {
					removeChild(prev, curr);
				}
				else 
					this->_root = NULL;
			}
			
			// case 2: node has one child
			else if (!curr->right) {
				node_pointer tmp = curr->left;
				curr->data = tmp->data;
				curr->left = NULL;
				curr = tmp;
			}
			else if (!curr->left) {
				node_pointer tmp = curr->right;
				curr->data = tmp->data;
				curr->right = NULL;
				curr = tmp;
			}

			// case 3: node has two children
			else {
				node_pointer tmp = min_node(curr->right);
				curr->data = tmp->data;
				curr = deletenodeHelper(curr->right, curr->data);
			}

			return (curr);
		}

		void deletenode (value_type key) {
			node_pointer deletedNode = deletenodeHelper(this->_root, key);
			if (deletedNode) {
				if (deletedNode->parent)
					updateBalance(deletedNode->parent);
				else if (this->_root)
					updateBalance(this->_root);
				this->_node_alloc.destroy(deletedNode);
				this->_node_alloc.deallocate(deletedNode, 1);
				this->_size--;
			}
			else
				std::cout << "Key not found." << std::endl;
		}

	// private:
	// 	std::string getColorStr(int color) const {
	// 		switch(color) {
	// 			case 0: return (LIGHTGREEN);
	// 			case 1: return (LIGHTBLUE);
	// 			case 2: return (LIGHTYELLOW);
	// 			case 3: return (LIGHTMAGENTA);
	// 			case 4: return (LIGHTCYAN);
	// 			default: return ("");
	// 		}
	// 	}

		void print2D(node_pointer curr, int space, std::string dir) const {
			// Base case
			if (curr == NULL)
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