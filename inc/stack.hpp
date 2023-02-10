#pragma once
#include "vector.hpp"


//Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
namespace ft{

	template <class T, class Container = ft::vector<T> >
	class stack{
		public:
			typedef T					value_type;
			typedef Container			container_type;
			typedef size_t				size_type;
			typedef value_type&			reference;
			typedef	const value_type&	const_reference;

		protected:
			container_type c;

		public:

		/*You have to take the structure of each standard container as reference. If a part of
		the Orthodox Canonical form is missing in it, do not implement it.*/
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr){}

			~stack(){}
			bool empty() const{return c.empty();}
			size_type size() const{return c.size();}
			value_type& top(){return c.back();}
			const value_type& top() const{return c.back();}
			void push (const value_type& val){c.push_back(val);}
			void pop(){return c.pop_back();}
	

		  
		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c == rhs.c;
		}	

		  
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c != rhs.c;
		}	

		  
		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c < rhs.c;
		}	

		  
		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c <= rhs.c;
		}	

		  
		friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c > rhs.c;
		}	

		  
		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
			return lhs.c >= rhs.c;
		}
	};
}