#pragma once

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
		//Tags are used to select the most efficient algorithm if your container is passed to one of the Standard Library functions from the <algorithm> library
		public:
			typedef T									value_type;
			typedef value_type*							pointer;
			typedef const pointer 						const_pointer;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef std::ptrdiff_t						difference_type;// It is a type able to represent the result of any valid pointer subtraction operation.
			typedef std::random_access_iterator_tag		iterator_category;// Empty class to identify the category of an iterator as a random-access iterator
			typedef vec_iterator< const value_type >	const_iterator;

		// https://cplusplus.com/reference/iterator/RandomAccessIterator/
		// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
			vec_iterator(void): it_ptr() {}//not sure if needed
			vec_iterator(pointer ptr)				: it_ptr(ptr) {}
			//TODO://wie sieht das nochmal ausgeschrieben aus?
			vec_iterator(vec_iterator const & src)	: it_ptr(src.it_ptr) {}
			vec_iterator& 				operator=(vec_iterator const & rhs) {if (this != &rhs) this->it_ptr = rhs.it_ptr;return *this;}
			~vec_iterator(void) {}
    		vec_iterator 				base() const {return this->it_ptr;}
			//getter function
			pointer						operator->() {return it_ptr;}
			const_pointer				operator->()const {return (it_ptr);}
			reference 					operator*() {return *it_ptr;}
			const_reference				operator*()const {return *it_ptr;}
  			vec_iterator& 				operator++() {++it_ptr;return *this;}
  			vec_iterator 				operator++(int) {vec_iterator tmp(*this); operator++(); return tmp;}//post operator//returns a copy of the it, bc the object in place should not be modified
			vec_iterator& 				operator--() {--it_ptr;return *this;}
  			vec_iterator 				operator--(int) {vec_iterator tmp(*this); operator--(); return tmp;}
			reference 					operator[](difference_type n) {return *(it_ptr + n);}
			const_reference 			operator[](difference_type n)const {return *(it_ptr + n);}
			vec_iterator& 				operator+=(difference_type n) {this->it_ptr += n; return *this;}
			vec_iterator& 				operator-=(difference_type n) {this->it_ptr -= n; return *this;}
    		vec_iterator  				operator+(difference_type n) const {return vec_iterator(this->it_ptr + n);}
    		vec_iterator 				operator-(difference_type n) const {return vec_iterator(this->it_ptr - n);}
			friend bool					operator==(const vec_iterator l, const vec_iterator r) {return l.base() == r.base();}
			friend bool					operator!=(const vec_iterator l, const vec_iterator r) {return l.base() != r.base();}
			friend bool					operator>(const vec_iterator l, const vec_iterator r) {return l.base() > r.base();}
			friend bool					operator>=(const vec_iterator l, const vec_iterator r) {return l.base() >= r.base();}
			friend bool					operator<(const vec_iterator l, const vec_iterator r) {return l.base() < r.base();}
			friend bool					operator<=(const vec_iterator l, const vec_iterator r) {return l.base() <= r.base();}
			friend difference_type		operator-(const vec_iterator l, const vec_iterator r) {return l.base() - r.base();}
			//friend for the non member overloads, if them both parameters don't get changed by the function

		private:
			pointer	it_ptr;

	};
	template< class IT >
	vec_iterator<IT>				operator+(typename vec_iterator<IT>::difference_type n, const vec_iterator<IT> &r) {return n + r.base();}
}