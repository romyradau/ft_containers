#include 	"map.hpp"
// #include <map>


int main(){

	// ft::map<int, std::string> my_map;
	// ft::map<int, std::string>::iterator mit;
	// ft::map<int, std::string>::reverse_iterator rmit;

	// my_map.insert(ft::pair<int, std::string>(42, "Hello"));

	ft::map<int, std::string> m;
	ft::pair<const int, std::string> pair = ft::make_pair<const int, std::string>(42, "Romyy");
	m.insert(pair);
	ft::avl_tree<int, std::string> tree = m.getTree();

	std::cout << tree.getRoot()->data.first << " " << tree.getRoot()->data.second << std::endl;
}