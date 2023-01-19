#pragma once
#include "romyVector.hpp"

//Concretely, an iterator is a simple class that provides a bunch of operators
//In fact, iterators are a generalization of pointers, which are often used as a foundation when writing the iterator itself.
/*	
1	Input Iterator 			Can scan the container forward only once, can't change the value it points to (read-only);
2 	Output Iterator 		Can scan the container forward only once, can't read the value it points to (write-only);
3 	Forward Iterator 		Can scan the container forward multiple times, can read and write the value it points to;
4 	Bidirectional Iterator 	Same as previous one but can scan the container back and forth;
5 	Random Access Iterator 	Same as previous one but can access the container also non-sequentially (i.e. by jumping around);
6 	Contiguous Iterator 	Same as previous one, with the addition that logically adjacent elements are also physically adjacent in memory.*/


//https://cplusplus.com/reference/iterator/iterator/

namespace ft{
	template<typename T>//will be put as parameter next to class declaration
	class vec_iterator{
		// C++ expects some properties from an iterator:
		using value_type		= T
		// using value_type = typename Vector::value_type
		using pointer			= value_type*;
		using const_pointer		= const pointer;
		using reference			= value_type&;
		using const_reference	= const reference;
		using difference_type 	= std::ptrdiff_t;// It is a type able to represent the result of any valid pointer subtraction operation.
		using iterator_category = std::random_access_iterator_tag;// Empty class to identify the category of an iterator as a random-access iterator:
		using const_iterator	= vec_iterator< const value_type >;

    	// typedef Category  iterator_category;
		// typedef T		  value_type;
    	// typedef Pointer   pointer;
    	// typedef Reference reference;
    	// typedef Distance  difference_type;

		// https://cplusplus.com/reference/iterator/RandomAccessIterator/
		public:
			// vec_iterator(void): it_ptr() {}//not sure if needed
			vec_iterator(pointer ptr): it_ptr(ptr) {}
			TODO://wie sieht das nochmal ausgeschrieben aus?
			vec_iterator(vec_iterator const & src) : it_ptr(src.it_ptr) {}
			vec_iterator& 				operator=(vec_iterator const & rhs) {
										if (this != &rhs)
											this->it_ptr = rhs.it_ptr;
										return *this;
			}
			//TODO:wie kann man das in einer Zeile schreiben?
			~vec_iterator(void) {}
  			bool 						operator==(vec_iterator const & rhs) const {return it_ptr==rhs.it_ptr;}//goes to the bool==operator of teh pointer object
  			bool 						operator!=(vec_iterator const & rhs) const {return it_ptr!=rhs.it_ptr;}
			pointer						operator->() {return it_ptr;}
			reference 					operator*() {return *it_ptr;}
			//*a = t
  			vec_iterator& 				operator++() {++it_ptr;return *this;}
  			vec_iterator 				operator++(int) {vec_iterator tmp(*this); operator++(); return tmp;}//post operator//returns a copy of the it, bc the object in place should not be modified
			vec_iterator& 				operator--() {--it_ptr;return *this;}
  			vec_iterator 				operator--(int) {vec_iterator tmp(*this); operator--(); return tmp;}
			//*a++, *a--
			//a + n, n + a, a - n, a - b
			//a < b,a > b,a <= b,a >= b
			reference 					operator[](int index) {return *(it_ptr + index);}
			vec_iterator& 				operator+=(difference_type n) {this.it_ptr += n; return *this}
			vec_iterator& 				operator-=(difference_type n) {this.it_ptr -= n; return *this}
    		vec_iterator  				operator+ (difference_type n) const {return vec_iterator(this->it_ptr + n);}
    		vec_iterator 				operator- (difference_type n) const {return vec_iterator(this->it_ptr - n);}
    		// vec_iterator 				base() const {return this->it_ptr;}


			TODO://which ones are missing?
			//TODO: was macht diese base function genau?
			//TODO: inbuilt templates

		private:
			pointer	it_ptr;

	}
} 