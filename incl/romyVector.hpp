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
#include "typeTraits.hpp"


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
			size_type								_size; //actual space//end
			allocator_type							_alloc; //allocator object used by Vector
			pointer									_pointer; //pointer to Vector

			size_type	new_capacity(size_type old_cap);


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


			size_type 			capacity() const{return this->_cap;}
			size_type 			size() const{return this->_size;}
			size_type 			max_size() const {return this->_alloc.max_size();}//possible allocatable space
			void 				resize (size_type n, value_type val = value_type());
			// void 			resize (size_type n, value_type val = value_type());
			reference 			operator[](size_type n){return this->_pointer[n];}
			const_reference 	operator[](size_type n) const{return this->_pointer[n];}
			reference 			at(size_type idx) { if (idx >= this->_size)  throw std::out_of_range("ft::out_of_range"); return (this->_pointer[idx]); }
			const_reference 	at(size_type idx) const { if (idx >= this->_size)  throw std::out_of_range("ft::out_of_range"); return (this->_pointer[idx]); }
			reference 			front() { return (*(this->_pointer)); }
			const_reference 	front() const { return (*(this->_pointer)); }
			reference 			back() { return (*(this->_pointer + this->_size - 1)); }
			const_reference 	back() const { return (*(this->_pointer + _size) - 1); }
			pointer 			data() { return (this->_pointer); }
			const_pointer 		data() const { return (this->_pointer); }
			void 				clear();
			bool 				empty() const { return (!this->_size); }
			void 				reserve (size_type n);
			void 				swap (Vector& x);
			
			// Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			template <class InputIterator>  void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
			//so that the two functions can be distinguished
			void assign (size_type n, const value_type& val);
			void push_back (const value_type& val);
			void pop_back();
			iterator insert(iterator pos, const_reference val);
			void insert(iterator pos, size_type n, const_reference val);
			template <class InputIterator> void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL);



			allocator_type get_allocator() const{return this->_alloc;}
			private:

			void _insert_construct_end(size_type curr, size_type n) { // helper func for fill and range insert() :-)
				for (size_type last_el = this->_size - 1; last_el >= curr; --last_el) {
					size_type new_last_el = last_el + n;
					this->_alloc.construct(this->_pointer + new_last_el, this->_pointer[last_el]);
					this->_alloc.destroy(this->_pointer + last_el);
					if (!last_el) // protection if pos is at the beginning :D
						break ;
				}
			}
			void _realloc(size_type new_cap) {
				size_type old_cap = this->_cap;

				T* newData = (this->_alloc).allocate(new_cap);

				if (new_cap < this->_size)
					this->_size = new_cap;
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(newData + i, this->_pointer[i]);
				this->_cap = new_cap;

				iterator it = begin();
				iterator ite = end();
				for (; it != ite; ++it)
					(this->_alloc).destroy(&(*it));
				if (this->_pointer)
					(this->_alloc).deallocate(this->_pointer, old_cap);

				this->_pointer = newData;
			}

	};

	//CINSTRUCT Vector
	//Constructs an empty container, with no elements.
	//allocator_type() ruft den constructor vom std::allocator auf
	//TODO:die schreibweise, den Zusammenhang verstehe ich nicht, warum muss ich bei Vector <T, Alloc> angeben??
	template<typename T, class Alloc>
	Vector<T, Alloc>::Vector(const allocator_type &alloc){
		_cap = 0;
		_size = 0;
		_alloc = alloc; //inbuilt it knows that it looks for std::allocator<T>
		_pointer = NULL;
	}

	//Constructs a container with n elements. Each element is a copy of val.
	//mit value_type() ist T vom Vector gemeint == hier werden z.b. 5, int allociert
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
		clear();//Removes all elements from the Vector (which are destroyed), leaving the container with a size of 0.
		if (this->_cap < x._size)
			reserve(x._cap);
		this->_size = x._size;
		for (size_type i = 0; i < x._size; i++)
			this->_alloc.construct(&this->_pointer[i], x._pointer[i]);	
		return *this;
	}

	//Vector DESTRUCTOR
	template<typename T, class Alloc>
	Vector<T, Alloc>::~Vector(){
		for(size_t i = 0; i < this->_size; i++)
			this->_alloc.destroy(&this->_pointer[i]); //destroyed aber noch nicht deallocated
		this->_alloc.deallocate(this->_pointer, this->_cap); // braucht kein [], deallocated so viele items wie einsta allocated
	}

	template<typename T, class Alloc>
	typename Vector<T, Alloc>::size_type	Vector<T, Alloc>::new_capacity(size_type old_cap){
		size_type n;
		n = 1;
		while (n < old_cap)
			n *= 2;
		return n;
	}

	template<typename T, class Alloc>
	void Vector<T, Alloc>::push_back (const value_type& val){

		if (this->_size != _cap){
			this->_alloc.construct(this->_pointer + this->_size, val);
			++this->_size;
		}
		else{
			reserve(new_capacity(this->_size + 1));
			this->_alloc.construct(this->_pointer + this->_size, val);
			++this->_size;
		}
			
	}
	template<typename T, class Alloc>
	void Vector<T, Alloc>::pop_back(){
					if (this->_size > 0) {
				--this->_size;
				this->_alloc.destroy(this->_pointer + this->_size);
			}
	}

	template<typename T, class Alloc>
	void Vector<T, Alloc>::assign (size_type n, const value_type& val){
		clear();
		for (size_type i = 0; i < n; i++)
			push_back(val);
		std::cout << "normal assign" <<std::endl;
	}

	template<typename T, class Alloc>
	template <class InputIterator>
	void Vector<T, Alloc>::assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*){
		clear();
	typename InputIterator::difference_type range = last - first;
		if (range > this->_cap)
			reserve(range);
		std::cout << "INPUTITERATOR aasign" << std::endl;
		for (; first != last; first++){
			this->push_back(*first);
		}
	}
	//TODO: ft::enable if und so ...

	template<typename T, class Alloc>
	void 			Vector<T, Alloc>::resize (size_type n, value_type val){

		if (n < size()) {
			while (size() > n)
			this->pop_back();
		}
		else if (n > size()) {
			if (n > this->_cap)
				this->_realloc(n);
			while (this->_size < n)
				this->push_back(val);
			}
		}


	// insert single element
	template<typename T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator pos, const_reference val) {
		size_type res = pos - begin(); // NOTE: address change so you have to save it :)
		this->insert(pos, 1, val);
		return (iterator(this->_data + res));
	}
	// insert fill
	template<typename T, class Alloc>
	void Vector<T, Alloc>::insert(iterator pos, size_type n, const_reference val) {
		size_type curr = pos - begin();
		std::cout << curr << std::endl;
		if (this->_size + n > this->_cap)
			_realloc(this->_size + n);
		this->_insert_construct_end(curr, n);
		for (size_type i = 0; i < n; ++i, ++curr)
			this->_alloc.construct(this->_pointer + curr, val);
		this->_size += n;
	}
	// insert range
	template<typename T, class Alloc>
	template <class InputIterator>
	void Vector<T, Alloc>::insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type*)
	{
		size_type curr = pos - begin();
		size_type n = last - first;
		if (this->_size + n >= this->_cap)
			_realloc(this->_cap + n);
		this->_insert_construct_end(curr, n);
		for (; first != last; ++curr, ++first)
			this->_alloc.construct(this->_pointer + curr, *first);
		this->_size += n;
	}
	template<typename T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase (iterator position){
		iterator res = position;
		if (position + 1 != end()) {
		while (position + 1 != end()) {
			*position = *(position + 1);
			++position;
		}
	}
	this->pop_back();
	return (res);
	}

	template<typename T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase (iterator first, iterator last){
		size_type pos = first - begin();
		size_type res = pos;
		size_type n = last - first;

		for (;first != last; ++first)
			this->_alloc.destroy(first.base());
		for (; last != end(); ++last, ++pos) {
			this->_alloc.construct(this->_data + pos, *last);
			this->_alloc.destroy(last.base());
		}
		this->_size -= n;
		return (iterator(this->_data + res));
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
		if (n > this->max_size())
				throw std::length_error("length_error");
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

	template <class T>
	void helper_swap ( T& a, T& b ){
	  T c(a);
	  a=b;
	  b=c;
	}
	
	template<typename T, class Alloc>
	void Vector<T, Alloc>::swap (Vector<T, Alloc>& x){
		ft::helper_swap(this->_alloc, x._alloc);
		ft::helper_swap(this->_cap, x._cap);
		ft::helper_swap(this->_poinetr, x._pointer);
		ft::helper_swap(this->_size, x._size);

	}

	// template<typename T, class Alloc>
	// Vector<T, Alloc>::iterator Vector<T, Alloc>::insert (iterator position, const value_type& val){

	// }
	

	// template<typename T, class Alloc>
	// void 	Vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val){

	// }

	// template<typename T, class Alloc>
	// template<class InputIterator>
	// void Vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last){

	// }

	template <class T, class Alloc>  
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
//check sizes, then compare
		if (lhs.size() == rhs.size())
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		return false;
	}


	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
		return !(lhs == rhs);
	}


	template <class T, class Alloc>
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template <class T, class Alloc>
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
        return !(rhs < lhs);

		//true???
	}


	template <class T, class Alloc>
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
		return rhs < lhs;
	}


	template <class T, class Alloc>
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs){
		return !(lhs < rhs);

	}

/* true if all the elements in the range [first1,last1) compare equal to those of the range starting at first2, and false otherwise.*/
	template <class InputIterator1, class InputIterator2>
  	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ){
	  while (first1!=last1) {
	    if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
	      return false;
	    ++first1; ++first2;
	  }
	  return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred){
			  while (first1!=last1) {
	    if (!pred(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
	      return false;
	    ++first1; ++first2;
	  }
	  return true;
	}
	/*Lexicographical order is nothing but the dictionary order or preferably the order in which words appear in the dictonary. For example, let's take three strings, "short", "shorthand" and "small". In the dictionary, "short" comes before "shorthand" and "shorthand" comes before "small". This is lexicographical order.*/
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
  		while (first1!=last1)
  		{
  		  if (first2==last2 || *first2<*first1) return false;
  		  else if (*first1<*first2) return true;
  		  ++first1; ++first2;
  		}
  		return (first2!=last2);
	}


	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
  		while (first1!=last1)
  		{
  		  if (comp(first2==last2 || *first2<*first1)) return false;
  		  else if (comp(*first1<*first2)) return true;
  		  ++first1; ++first2;
  		}
  		return (first2!=last2);
	}
/*After the call to this member function, the elements in x are those which were in y before the call, and the elements of y are those which were in x.*/
	template <class T, class Alloc>
	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y){
		x.swap(y);

	}


}