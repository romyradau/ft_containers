#pragma once

#define COUNT 10

#include <iostream>
#include <algorithm>

namespace ft {

	template <typename T>
	struct node {
		typedef T					value_type;
		typedef node<value_type>*	ptr;
		typedef size_t				size_type;

		value_type					data;
		ptr 					parent;
		ptr 					left;
		ptr 					right;
		int 					bf;

		node(const value_type& data = value_type()): data(data), parent(NULL), left(NULL), right(NULL), bf(0) {}

		};

	template <typename T>
	class avl_tree {
		public:
			typedef T						value_type;
			typedef ft::node<value_type>	node;
			typedef typename node::ptr		ptr;

		private:
			ptr _root;

		public:
			avl_tree(): _root(NULL) {}

			ptr get_root() const { return (this->_root); }

			void leftRotate(ptr x) {
				ptr y = x->right;
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

				// update the balance factor
				x->bf = x->bf - 1 - std::max(0, y->bf);
				y->bf = y->bf - 1 + std::min(0, x->bf);
			} 

			void rightRotate(ptr x) {
				ptr y = x->left;
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

				// update the balance factor
				x->bf = x->bf + 1 - std::min(0, y->bf);
				y->bf = y->bf + 1 + std::max(0, x->bf);
			}

			ptr rebalance(ptr curr) {
				if (curr->bf > 0) {
					if (curr->right->bf < 0) {
						std::cout << "right left rotate" << std::endl;
						rightRotate(curr->right);
						leftRotate(curr);
					} else {
						std::cout << "left rotate" << std::endl;
						leftRotate(curr);
					}
					return (curr->parent);
				} 
				else if (curr->bf < 0) {
					if (curr->left->bf > 0) {
						std::cout << "left right rotate" << std::endl;
						leftRotate(curr->left);
						rightRotate(curr);
					} else {
						std::cout << "right rotate" << std::endl;
						rightRotate(curr);
					}
					return (curr->parent);
				}
				return (curr);
			}

			void updateBalance(ptr curr) {

				if (curr->bf < -1 || curr->bf > 1) {
					this->rebalance(curr);
					std::cout << "Rebalancing needed." << std::endl;
					return ;
				}
				if (curr->parent != NULL) {
					if (curr == curr->parent->left)
						curr->parent->bf -= 1;
					if (curr == curr->parent->right)
						curr->parent->bf += 1;
					if (curr->parent->bf != 0)
						this->updateBalance(curr->parent);
				}
			}

			void insert(value_type key) {
				// PART 1: Ordinary BST insert
				ptr curr = new node(key);

				ptr y = NULL;
				ptr x = this->_root;

				while (x != NULL) {
					y = x;
					if (curr->data < x->data)
						x = x->left;
					else
						x = x->right;
				}

				// y is parent of x
				curr->parent = y;
				if (y == NULL)
					this->_root = curr;
				else if (curr->data < y->data)
					y->left = curr;
				else
					y->right = curr;

				// PART 2: re-balance the node if necessary
				this->updateBalance(curr);
			}


			ptr maximum(ptr node) {
			while (node->right != nullptr) {
				node = node->right;
			}
			return node;
			}
	
			// find the node with the minimum key
			ptr minimum(ptr curr) {
				while (curr->left != NULL) {
					curr = curr->left;
				}
				return (curr);
			}


	ptr successor(ptr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != NULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		ptr y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	ptr predecessor(ptr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != NULL) {
			return maximum(x->left);
		}

		ptr y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}
			ptr deletenodeHelper(ptr curr, value_type key) {
				ptr p;
				// search the key
				if (curr == NULL) return (curr);
				else if (key < curr->data) {
					curr->left = deletenodeHelper(curr->left, key);
					curr->bf += 1;
					return rebalance(curr);
					//return rebalance von dem neuen root des subtrees

				}
				else if (key > curr->data) {
					curr->right = deletenodeHelper(curr->right, key);
					curr->bf -= 1;
					return rebalance(curr);
				}
				else {
					// the key has been found, now delete it
					p = curr->parent;
					// case 1: curr is a leaf node
					if (curr->left == NULL && curr->right == NULL) {
						delete curr;
						curr = NULL;
					}

					// case 2: curr has only one child
					else if (curr->left == NULL) {
						ptr temp = curr;
						curr = curr->right;
						delete temp;
					}

					else if (curr->right == NULL) {
						ptr temp = curr;
						curr = curr->left;
						delete temp;
					}

					// case 3: has both children
					else {
						ptr temp = minimum(curr->right);
						curr->data = temp->data;
						curr->right = deletenodeHelper(curr->right, temp->data);
					}

				// 	if (p)
				// 	{
				// 		// while(predecessor(p))
				// 		// p = minimum(this->_root);
				// 		updateBalance(p);
				// } 

				// Write the update balance logic here 
				// YOUR CODE HERE

				}
				return (curr);
			}

			ptr deletenode (value_type key) {
				ptr deletednode = deletenodeHelper(this->_root, key);
				// ptr deletednode = deletenodeHelper2(this->_root, key);
				return (deletednode);
			}

			void printHelper(ptr curr, std::string indent, bool last) const {
				// print the tree structure on the screen
				if (curr != NULL) {
					std::cout << indent;
					if (last) {
						std::cout << "R----";
						indent += "     ";
					}
					else {
						std::cout << "L----";
						indent += "|    ";
					}
					std::cout << curr->data << "( bf = " << curr->bf <<")" << std::endl;

					this->printHelper(curr->left, indent, false);
					this->printHelper(curr->right, indent, true);
				}
			}

			void prettyPrint() const {
				this->printHelper(this->_root, "", true);
			}

			void print2DUtil(ptr root, int space) const {
				// Base case
				if (root == NULL)
					return ;

				// Increase distance between levels
				space += COUNT;

				// Process right child first
				print2DUtil(root->right, space);

				// Print current node after space
				// count
				std::cout << std::endl;
				for (int i = COUNT; i < space; i++)
					std::cout << " ";
				std::cout << root->data << "(bf: " << root->bf << ")" << std::endl;

				// Process left child
				print2DUtil(root->left, space);
			}

			// Wrapper over print2DUtil()
			void print2D() const {
				// Pass initial space count as 0
				print2DUtil(this->_root, 0);
			}
	};
} 