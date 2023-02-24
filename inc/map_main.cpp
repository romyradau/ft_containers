#include 	"map.hpp"
// #include <map>


int main(){

	// ft::map<int, std::string> my_map;
	// ft::map<int, std::string>::iterator mit;
	// ft::map<int, std::string>::reverse_iterator rmit;

	// my_map.insert(ft::pair<int, std::string>(42, "Hello"));

	ft::map<int, std::string> m;
	std::cout << "xxx" << std::endl;



	ft::pair<const int, std::string> pair = ft::make_pair<const int, std::string>(42, "Romyy");
	ft::pair<const int, std::string> pair2 = ft::make_pair<const int, std::string>(666, "DEATH");

	ft::pair<ft::map<int, std::string>::iterator, bool> insert_res =  m.insert(pair);
	ft::map<int, std::string>::iterator insert_it = m.insert(m.begin(), pair2);
	std::cout << (insert_res.second ? "INSERTED" : "ALREADY INSERTED") << std::endl;
	insert_res =  m.insert(pair);
	std::cout << (insert_res.second ? "INSERTED" : "ALREADY INSERTED") << std::endl;
	std::cout << m[42] << std::endl;
	std::cout << m[22] << std::endl;
	m[22] = "abc";
	m[23] = "def";
	m[24] = "ghi";
	m[25] = "jkl";

	m.printMap();
	
	ft::map<int, std::string>::iterator it = m.begin();
	ft::map<int, std::string>::iterator ite = m.end();
	// for (; it != ite; ++it)
	// 	std::cout << *it << std::endl;

	m.erase(it, ite);

	std::cout << "\n\n---------\n\n";
	m.printMap();

	std::cout << "\n\n---------\n\n";

	
	// std::cout << "Size: " << m.size() << std::endl;
	// m.erase(25);
	// m.erase(666);
	// m.erase(42);
	// std::cout << "\n\n---------\n\n";
	// m.printMap();
	// std::cout << "Size: " << m.size() << std::endl;
	// std::cout << m.count(22) << std::endl;
	// std::cout << m.count(20) << std::endl;


  	// try {
  	//   m.at(11)=100;      // vector::at throws an out-of-range
  	//   m.at(42)= "Romyy";      // vector::at throws an out-of-range
  	// }
  	// catch (const std::out_of_range& oor) {
  	//   std::cerr << "Out of Range error: " << oor.what() << '\n';
  	// }
	// ft::map<int, std::string> m2;
	// m2.insert(begin_it, end_it);
	// ft::map<int, std::string>::iterator begin_it = m.begin();
	// ft::map<int, std::string>::iterator end_it = m.end();
	// ft::map<int, std::string>::reverse_iterator rev_begin_it = m.rbegin();
	// ft::map<int, std::string>::reverse_iterator rev_end_it = m.rend();
	// for (; rev_begin_it != rev_end_it; rev_begin_it++)
	// 	std::cout << rev_begin_it->first << std::endl;
		
	// ft::map<int, std::string>::iterator find_it = m.find(666);
	// m.erase(find_it);
	// m.printMap();

	// m.clear();
	// std::cout << "\n\n" << m.empty() << "\n\n" << std::endl;

	// m2.printMap();


	// ft::avl_tree<int, std::string> tree = m.getTree();

	// std::cout << tree.getRoot()->data.first << " " << tree.getRoot()->data.second << std::endl;
}