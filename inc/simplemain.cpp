#include "vector.hpp"
#include "iterator.hpp" 
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include <vector>
#include <sstream>
// #define vector std::vector



using namespace ft;
// extra function to print out our vector with yet unknown type
template<typename T>
void Printvector( const vector<T>& V){
	for( size_t i = 0; i < V.size(); i++)
		std::cout << V[i] << std::endl;
}

#define PRINT_POS std::cout << __FILE__ << " : " << __LINE__ << std::endl

int main(){

	// vector<int> first;
  	// vector<int> second (5,100);                       // four ints with value 100
  	// // vector<int> third (second.begin(),second.end());  // iterating through second
  	// vector<int> fourth (second);
	// fourth.push_back(200);
	// fourth.push_back(300);
	// // first.assign(5, 5);
	// first.assign(second.begin(), second.end());
	// Printvector(second);
	// std::cout << first.capacity() << std::endl;
	// // PRINT_POS;

	// first.assign(second.begin(), second.end());
	// // vector.PushBack("Hit");
	// // vector.PushBack("them");
	// // vector.PushBack("vector");

	// std::cout << first.max_size()<< std::endl;                             // empty vector of ints
	// Printvector(second);
	// Printvector(fourth);
	// second = first;
	// Printvector(second);
	// first.reserve(3);
	// first = fourth;
	// std::cout << first.size() <<std::endl;
	// first.clear();
	// std::cout << first.size() <<std::endl;
	// std::cout << "---------------"<< std::endl; 
	// vector<int>::iterator it;
	// reverse_iterator<vector<int>::iterator> rev_it;

	std::stringstream str("1 2 3 4 5 6 7 8 9 0 A B C D E F");
	std::istreambuf_iterator<char> it(str), end;
	std::cout << *end<< std::endl;

        // charvector v(2, 'U');
	vector<char> v(2, 'U');
	Printvector(v);
	std::cout << "size: " << v.size() << std::endl;

	std::cout << std::endl << std::endl;

	v.insert(v.end(), it, end);
	Printvector(v);
	std::cout << "size: " << v.size() << std::endl;


}
