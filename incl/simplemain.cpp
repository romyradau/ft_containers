#include "romyVector.hpp"
#include "vectorIterator.hpp" 
#include "iteratorTraits.hpp"
#include <vector>
// #define Vector std::vector



using namespace ft;
//extra function to print out our Vector with yet unknown type
template<typename T>
void PrintVector( const Vector<T>& V){
	for( size_t i = 0; i < V.size(); i++)
		std::cout << V[i] << std::endl;
}


int main(){

	Vector<int> first;
  	Vector<int> second (2,100);                       // four ints with value 100
  	// // Vector<int> third (second.begin(),second.end());  // iterating through second
  	Vector<int> fourth (second);
	// // vector.PushBack("Hit");
	// // vector.PushBack("them");
	// // vector.PushBack("vector");

	std::cout << first.max_size()<< std::endl;                             // empty vector of ints
	PrintVector(second);
	PrintVector(fourth);
	second = first;
	PrintVector(second);
	first.reserve(3);
	first = fourth;
	std::cout << first.size() <<std::endl;
	first.clear();
	std::cout << first.size() <<std::endl;
	std::cout << "---------------"<< std::endl; 
	Vector<int>::iterator it();



}
