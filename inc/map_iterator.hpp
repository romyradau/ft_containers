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
			// typedef	const value_type					const_value_type;
			typedef value_type*							pointer;
			typedef ft::node<value_type>*				node_pointer;
			typedef const pointer 						const_pointer;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef std::ptrdiff_t						difference_type;// It is a type able to represent the result of any valid pointer subtraction operation.
			typedef std::bidirectional_iterator_tag		iterator_category;// Empty class to identify the category of an iterator as a random-access iterator
			// typedef map_iterator< const value_type >	const_iterator;

		private:
			// pointer 			it_ptr;
			node_pointer	it_ptr;

		public:
			map_iterator(): it_ptr(NULL){}
			map_iterator(map_iterator const &src): it_ptr(src.it_ptr){}
			map_iterator(ft::node<value_type>* ptr): it_ptr(ptr){};
			operator	map_iterator<const value_type>() const { return map_iterator<const value_type>(reinterpret_cast<node<const value_type>* >(it_ptr)); }



			// template<class Iter>
			// map_iterator(const map_iterator<Iter>& i) : it_ptr(i.it_ptr()) {};
			// map_iterator(ft::node<const_value_type>* ptr): it_ptr(ptr){};

			// map_iterator(const_pointer cptr): it_ptr(ptr){};


			map_iterator&	operator=(map_iterator const & rhs){if (this!= &rhs) it_ptr = rhs.it_ptr; return *this;}

			// a == b 
			// a != b
			template< class Iter1, class Iter2 >
			friend bool					operator==(const map_iterator<Iter1> l, const map_iterator<Iter2> r) {return l.it_ptr == r.it_ptr;}
			template< class Iter1, class Iter2 >
			friend bool					operator!=(const map_iterator<Iter1> l, const map_iterator<Iter2> r) {return (l.it_ptr != r.it_ptr);}
			node_pointer base(){return this->it_ptr;}
			// *a
			// a->m
			pointer				operator->() {return &(operator*());}
			const_pointer		operator->()const {return &(operator*());}
			reference			operator*() {return it_ptr->data;}
			const_reference		operator*()const {return it_ptr->data;}

			map_iterator&		operator++(){
				if(it_ptr)
					it_ptr = it_ptr->successor(it_ptr);
				return *this;
			}
			map_iterator		operator++(int){map_iterator tmp = *this; ++*this; return tmp;}
			map_iterator&		operator--(){
				if(it_ptr)
					it_ptr = it_ptr->predecessor(it_ptr);
				return(*this);
			}
			map_iterator		operator--(int){map_iterator tmp = *this; --*this; return tmp;}

			};

	};