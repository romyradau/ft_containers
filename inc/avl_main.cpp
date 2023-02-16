#include <iostream>
#include "avl_tree.hpp"
#include "type_traits.hpp"

int main(){


	ft::avl_tree<int>	avl;
	avl.insert(10);
	avl.insert(11);
	avl.insert(23);
	avl.insert(7);
	avl.insert(110);
	avl.insert(100);
	avl.insert(55);
	avl.insert(50);
	avl.insert(66);
	avl.insert(14);

	// avl.printTree();
	// avl.deletenode(14);
	avl.printTree();
	std::cout << "\n\n\n";
	std::cout << "\n\n\n";
	// ft::avl_tree<int>::node_pointer pre;
	// ft::avl_tree<int>::node_pointer succ;

	// pre = avl.predecessor(avl.search(7));
	// succ = avl.successor(avl.search(110));
	// std::cout << pre->data << "	" << succ->data << std::endl;


	ft::avl_tree<int> avl_copy(avl);
	avl.deletenode(11);
	avl_copy.printTree();

	// int input;
	// while (std::cin >> input && input != 0) {
	// 	char mode;

	// 	std::cin >> mode;
	// 	if (mode == 'i')
	// 		avl.insert(input);
	// 	if (mode == 'd')
	// 	avl.deletenode(input);
	// 	avl.print2D();

	// }
}