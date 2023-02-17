#pragma once
#include <cstddef>
#include <iostream>
#include "avl_tree.hpp"

namespace ft{

	template <typename T >
	struct node;

	template<typename T>
	class map_iterator {

		public:
			typedef T									value_type;
			typedef value_type*							pointer;
			typedef const pointer 						const_pointer;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef std::ptrdiff_t						difference_type;// It is a type able to represent the result of any valid pointer subtraction operation.
			typedef std::bidirectional_iterator_tag		iterator_category;// Empty class to identify the category of an iterator as a random-access iterator
			typedef map_iterator< const value_type >	const_iterator;

		private:
			// pointer 			it_ptr;
			ft::node<value_type>*	it_ptr;

		public:
			map_iterator(): it_ptr(NULL){}
			map_iterator(map_iterator const &src): it_ptr(src.it_ptr){}
			map_iterator(ft::node<value_type>* ptr): it_ptr(ptr){};
			map_iterator&	operator=(map_iterator const & rhs){if (this!= &rhs) it_ptr = rhs.it_ptr; return *this;}

			// a == b 
			// a != b
			template< class Iter1, class Iter2 >
			friend bool					operator==(const map_iterator<Iter1> l, const map_iterator<Iter2> r) {return l.it_ptr == r.it_ptr;}
			template< class Iter1, class Iter2 >
			friend bool					operator!=(const map_iterator<Iter1> l, const map_iterator<Iter2> r) {return (l.it_ptr != r.it_ptr);}

			// *a
			// a->m
			pointer				operator->() {return it_ptr;}
			const_pointer		operator->()const {return it_ptr;}
			reference			operator*() {return *it_ptr;}
			const_reference		operator*()const {return *it_ptr;}

			map_iterator&		operator++(){if(!it_ptr) return *this; return(map_iterator(it_ptr->successor(it_ptr)));}
			// map_iterator&		operator++(){if(!it_ptr) return *this; return(map_iterator(T::successor(it_ptr)));}

			map_iterator		operator++(int){map_iterator tmp = *this; ++*this; return tmp;}
			map_iterator&		operator--(){if(!it_ptr) return *this; return(map_iterator(it_ptr->predecessor(it_ptr)));}
			map_iterator		operator--(int){map_iterator tmp = *this; --*this; return tmp;}

			};

	};