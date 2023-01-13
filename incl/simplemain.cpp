#include "romyVector.hpp"

//extra function to print out our Vector with yet unknown type
template<typename T>
void PrintVector( const Vector<T>& vector){
	for( size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;
}

int main(){

	Vector<std::string> vector;
	vector.PushBack("Hit");
	vector.PushBack("them");
	vector.PushBack("vector");
	vector.PopBack();
	vector.PushBack("Hit");
	vector.PushBack("them");
	vector.PopBack();
	vector.PushBack("vector");
	vector.Clear();

	vector.PushBack("vector");
	PrintVector(vector);
}
