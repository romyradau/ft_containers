#pragma once

#include <iostream>
#include <memory>
//for std::allocator
#include <limits>
#include <cstddef>
//ptrdiff_t
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <iterator>
#include "vectorIterator.hpp" 
#include "reverseIterator.hpp"

namespace ft{
	//TODO:geht das so oder muss ich's normal eingliedern?

	//The typedef-names are aliases for existing types, and are not declarations of new types.
	template<typename T, class Alloc = std::allocator<T> >
	class Vector{
		public: 
		typedef	T									value_type;
		typedef	Alloc								allocator_type;
		typedef	size_t								size_type;
		
		//originally allocator_type::reference why then value_type& and not Alloc&??
		//->the standard default allocator, automatically returns &x
		//so it's basically the same!
		typedef	value_type&							reference;
		typedef const value_type&					const_reference;
		typedef	value_type*							pointer;
		typedef	const value_type*					const_pointer;

		//extra header for the iterators
		typedef	ft::vec_iterator<value_type> 			iterator;
		typedef ft::vec_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		//das ist die gleiche schreibweise nur andersrum
		//links alias rechst typedef		 
		// typedef ft::vec_iterator<value_type>		iterator;
		// typedef ft::vec_iterator<const value_type>	const_iterator;
		// typedef	ft::vec_iterator<value_type>		reverse_iterator;
		// typedef ft::vec_iterator<const value_type>	const_reverse_iterator;

		// difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type
		// will be in iterator traits

		private:
			size_type								_cap; //avaialble space
			size_type								_size; //actual space
			allocator_type							_alloc; //allocator object used by vector
			pointer									_pointer; //pointer to vector

		public:
			explicit Vector (const allocator_type& alloc = allocator_type());
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

			//TODO: den vielleicht erst nach IteratorImplementierung?
			// template <class InputIterator>         Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			Vector (const Vector& x);

			Vector& operator= (const Vector& x);
			~Vector();

			/*ITERATOR*/
			iterator			begin(){return iterator(this->_pointer);}
			iterator			begin()const {return const_iterator(this->_pointer);}
			iterator			end(){return iterator(this->_pointer + _size);}
			iterator			end()const {return const_iterator(this->_pointer + _size);}
			reverse_iterator	rbegin(){return reverse_iterator(end());}
			reverse_iterator	rbegin()const {return const_reverse_iterator(end());}
			reverse_iterator	rend(){return reverse_iterator(begin());}
			reverse_iterator	rend()const{return const_reverse_iterator(begin());}
			//USES THE FUNCTION RESULT AS PARAM FOR THE CINSTRUCTORS
			
	//functions needed for testing
			size_type 		size() const{return this->_size;}
			size_type 		max_size() const {return this->_alloc.max_size();}//possible allocatable space
			// void 			resize (size_type n, value_type val = value_type());
			reference 		operator[](size_type n){return this->_pointer[n];}
			const_reference operator[](size_type n) const{return this->_pointer[n];}
			void 			clear();
			void 			reserve (size_type n);
			// Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.


	};

	//CINSTRUCT VECTOR
	//Constructs an empty container, with no elements.
	//allocator_type() ruft den constructor vom std::allocator auf
	//TODO:die schreibweise, den Zusammenhang verstehe ich nicht, warum muss ich bei vector <T, Alloc> angeben??
	template<typename T, class Alloc>
	Vector<T, Alloc>::Vector(const allocator_type &alloc){
		_cap = 0;
		_size = 0;
		_alloc = alloc; //inbuilt it knows that it looks for std::allocator<T>
		_pointer = NULL;
		printf("hallo\n");
	}

	//Constructs a container with n elements. Each element is a copy of val.
	//mit value_type() ist T vom vector gemeint == hier werden z.b. 5, int allociert
	template<typename T, class Alloc>
	Vector<T, Alloc>::Vector(size_type n, const value_type& val, const allocator_type &alloc){
		_cap = n;
		_size = n;	
		_alloc = alloc; //inbuilt it knows that it looks for std::allocator<T>
		_pointer = this->_alloc.allocate(n); // allocated aber nicht constructed
		for (size_t i = 0; i < n; i++)
			this->_alloc.construct(_pointer + i, val);
	}

	//shallow copy constructor - ain't shallow, goes to assign= which goes directs to reserve function, which allocates
	template<typename T, class Alloc>
	Vector<T, Alloc>::Vector(const Vector& x){
		_cap = 0;
		_size = 0;
		_alloc = allocator_type();//TODO:?
		_pointer = NULL;
		*this = x;
	}

	//ASSIGN CONTENT WITH FUNCTIONS
	// template<typename T, class Alloc>
	// Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector<T, Alloc>& x){
	// 	if (*this != x)
	// 		assign(x.begin(), x.end());
	// 	return *this;
	// }

	//ASSIGN CONTENT WITHOUT
	//Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
	template<typename T, class Alloc>
	Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector<T, Alloc>& x){
		clear();//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		if (this->_cap < x._size)
			reserve(x._cap);
		this->_size = x._size;
		for (size_type i = 0; i < x._size; i++)
			this->_alloc.construct(&this->_pointer[i], x._pointer[i]);	
		return *this;
	}

	//VECTOR DESTRUCTOR
	template<typename T, class Alloc>
	Vector<T, Alloc>::~Vector(){
		for(size_t i = 0; i < this->_size; i++)
			this->_alloc.destroy(&this->_pointer[i]); //destroyed aber noch nicht deallocated
		this->_alloc.deallocate(this->_pointer, this->_cap); // braucht kein [], deallocated so viele items wie einsta allocated
	}

	template<typename T, class Alloc>
	void 		Vector<T, Alloc>::clear(){
		//TODO: vielleicht muss heir noch ne if Bedingung hin??
		for(size_t i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_pointer + i);
		this->_size = 0;
	}


	template<typename T, class Alloc>
	void 		Vector<T, Alloc>::reserve(size_type n){
		//TODO::The function throws length_error if n is greater than max_size.
		if (this->_cap < n){
			pointer	tmp;
			tmp = this->_alloc.allocate(n);
			for (size_t i = 0; i < this->_size; i++){
				this->_alloc.construct(tmp + i, this->_pointer[i]);
				this->_alloc.destroy(this->_pointer + i);
			}
			this->_alloc.deallocate(this->_pointer, this->_cap);
			this->_cap = n;
			this->_pointer = tmp;
		}
	}


}