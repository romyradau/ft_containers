#include 	"map.hpp"
// #include <map>


int main(){

	// ft::map<int, std::string> my_map;
	// ft::map<int, std::string>::iterator mit;
	// ft::map<int, std::string>::reverse_iterator rmit;

	// my_map.insert(ft::pair<int, std::string>(42, "Hello"));

	ft::map<int, std::string> m;
	ft::pair<const int, std::string> pair = ft::make_pair<const int, std::string>(42, "Romyy");
	ft::pair<const int, std::string> pair2 = ft::make_pair<const int, std::string>(666, "DEATH");

	ft::pair<ft::map<int, std::string>::iterator, bool> insert_res =  m.insert(pair);
	ft::map<int, std::string>::iterator insert_it = m.insert(m.begin(), pair2);
	m.printMap();
	std::cout << (insert_res.second ? "INSERTED" : "ALREADY INSERTED") << std::endl;
	insert_res =  m.insert(pair);
	std::cout << (insert_res.second ? "INSERTED" : "ALREADY INSERTED") << std::endl;
	std::cout << m[42] << std::endl;
	std::cout << m[22] << std::endl;
	std::cout << "end" << std::endl;
	m[22] = "222";
  	try {
  	  m.at(11)=100;      // vector::at throws an out-of-range
  	  m.at(42)= "Romyy";      // vector::at throws an out-of-range
  	}
  	catch (const std::out_of_range& oor) {
  	  std::cerr << "Out of Range error: " << oor.what() << '\n';
  	}
	m.printMap();


	// ft::avl_tree<int, std::string> tree = m.getTree();

	// std::cout << tree.getRoot()->data.first << " " << tree.getRoot()->data.second << std::endl;
}