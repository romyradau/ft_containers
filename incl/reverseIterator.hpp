#pragma once
#include "iteratorTraits.hpp"

namespace ft{
	template<class IT>
	class reverse_iterator{
		typedef IT											iterator_type;
		typedef iterator_traits<IT>::iterator_category		iterator_category;
		typedef iterator_traits<IT>::value_type				value_type;
		typedef iterator_traits<IT>::difference_type		difference_type;
		typedef iterator_traits<IT>::pointer				pointer;
		typedef iterator_traits<IT>::reference				reference;

		// https://cplusplus.com/reference/iterator/RandomAccessIterator/
		// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
		public:
			reverse_iterator(void): this->m_it() {}
			explicit reverse_iterator (iterator_type it): this->m_it(it){}
			//TODO://wie sieht das nochmal ausgeschrieben aus?
			template <class IT>  reverse_iterator (const reverse_iterator<IT>& rev_it): this->m_it(rev_it.base())
			// reverse_iterator& 				operator=(reverse_iterator const & rhs) {if (this != &rhs) this->m_it = rhs.m_it;return *this;}
			~reverse_iterator(void) {}
    		iterator_type 				base() const {return this->m_it;}


			
			reference 					operator*() const {return *this->m_it;}
			pointer						operator->() {return this->m_it;}
  			reverse_iterator& 				operator++() {++this->m_it;return *this;}
  			reverse_iterator 				operator++(int) {reverse_iterator tmp(*this); operator++(); return tmp;}//post operator//returns a copy of the it, bc the object in place should not be modified
			reverse_iterator& 				operator--() {--this->m_it;return *this;}
  			reverse_iterator 				operator--(int) {reverse_iterator tmp(*this); operator--(); return tmp;}
			reference 					operator[](int index) {return *this->m_it + index);}
			const_reference 			operator[](int index)const {return *(this->m_it + index);}
			reverse_iterator& 				operator+=(difference_type n) {this->m_it += n; return *this;}
			reverse_iterator& 				operator-=(difference_type n) {this->m_it -= n; return *this;}
    		reverse_iterator  				operator+(difference_type n) const {return reverse_iterator(this->m_it + n);}
    		reverse_iterator 				operator-(difference_type n) const {return reverse_iterator(this->m_it - n);}
			friend bool					operator==(const reverse_iterator l, const reverse_iterator r) {return l.base() == r.base();}
			friend bool					operator!=(const reverse_iterator l, const reverse_iterator r) {return l.base() != r.base();}
			friend bool					operator>(const reverse_iterator l, const reverse_iterator r) {return l.base() > r.base();}
			friend bool					operator>=(const reverse_iterator l, const reverse_iterator r) {return l.base() >= r.base();}
			friend bool					operator<(const reverse_iterator l, const reverse_iterator r) {return l.base() < r.base();}
			friend bool					operator<=(const reverse_iterator l, const reverse_iterator r) {return l.base() <= r.base();}
			friend difference_type		operator-(const reverse_iterator l, const reverse_iterator r) {return l.base() - r.base();}
			//friend for the non member overloads, if them both parameters don't get changed by the function

		private:
			iterator_type	m_it;

	};
	//muss geerbt werden, reicht der constructor aus?
	template< class IT >
	reverse_iterator<IT>				operator+(typename reverse_iterator<IT>::difference_type n, const reverse_iterator<IT> &r) {return n + r.base();}
}