#include "romyVector.hpp"
#include <vector>
#define Vector std::vector

using namespace ft;
//extra function to print out our Vector with yet unknown type
template<typename T>
void PrintVector( const Vector<T>& vector){
	for( size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;
}



int main(){

	Vector<int> first;                                // empty vector of ints
  	Vector<int> second (2,100);                       // four ints with value 100
  	// Vector<int> third (second.begin(),second.end());  // iterating through second
  	Vector<int> fourth (second);
	// vector.PushBack("Hit");
	// vector.PushBack("them");
	// vector.PushBack("vector");

	PrintVector(first);
	PrintVector(second);
	PrintVector(fourth);

}
