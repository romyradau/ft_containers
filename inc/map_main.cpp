#include 	"map.hpp"
// #include <map>


int main(){

	ft::map<int, std::string> my_map;
	ft::map<int, std::string>::iterator mit;
	ft::map<int, std::string>::reverse_iterator rmit;

	my_map[42] = "Hello";

	// std::map<int, int>	mapp;
	// std::map<int, int>::iterator it;
	// it.base();
}