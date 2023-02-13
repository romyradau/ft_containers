#include <iostream>
#include "avl_tree.hpp"
#include "type_traits.hpp"

int main(){

	ft::avl_tree<int>	avl;
	avl.insert(58);
	avl.insert(46);
	avl.insert(43);
	avl.insert(634);
	avl.insert(11);
	avl.insert(10);
	avl.insert(55);
	avl.insert(50);
	avl.insert(66);

	avl.insert(14);

	avl.print2D();
	std::cout << std::endl << std::endl;
	avl.deletenode(58);
	avl.print2D();

}