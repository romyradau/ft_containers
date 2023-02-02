#include "romyVector.hpp"
#include "vectorIterator.hpp" 
#include "iteratorTraits.hpp"
#include "reverseIterator.hpp"
#include <vector>
// #define Vector std::vector



using namespace ft;
// extra function to print out our Vector with yet unknown type
template<typename T>
void PrintVector( const Vector<T>& V){
	for( size_t i = 0; i < V.size(); i++)
		std::cout << V[i] << std::endl;
}

#define PRINT_POS std::cout << __FILE__ << " : " << __LINE__ << std::endl

int main(){

	Vector<int> first;
  	Vector<int> second (5,100);                       // four ints with value 100
  	// Vector<int> third (second.begin(),second.end());  // iterating through second
  	Vector<int> fourth (second);
	fourth.push_back(200);
	fourth.push_back(300);
	// first.assign(5, 5);
	first.assign(second.begin(), second.end());
	PrintVector(first);
	std::cout << first.capacity() << std::endl;
	// PRINT_POS;

	// first.assign(second.begin(), second.end());
	// // vector.PushBack("Hit");
	// // vector.PushBack("them");
	// // vector.PushBack("vector");

	// std::cout << first.max_size()<< std::endl;                             // empty vector of ints
	// PrintVector(second);
	// PrintVector(fourth);
	// second = first;
	// PrintVector(second);
	// first.reserve(3);
	// first = fourth;
	// std::cout << first.size() <<std::endl;
	// first.clear();
	// std::cout << first.size() <<std::endl;
	// std::cout << "---------------"<< std::endl; 
	// Vector<int>::iterator it;
	// reverse_iterator<Vector<int>::iterator> rev_it;





}
