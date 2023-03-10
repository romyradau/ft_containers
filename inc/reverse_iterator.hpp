#pragma once
#include "iterator_traits.hpp"

/*reverse_iterator point to the it - 1 element*/
namespace ft{
	template<class IT>
	class reverse_iterator{
		public:
			typedef IT													iterator_type;
			typedef typename iterator_traits<IT>::iterator_category		iterator_category;
			typedef typename iterator_traits<IT>::value_type			value_type;
			typedef typename iterator_traits<IT>::difference_type		difference_type;
			typedef typename iterator_traits<IT>::pointer				pointer;
			typedef typename iterator_traits<IT>::reference				reference;
			typedef reverse_iterator< const value_type >				const_reverse_iterator;
//does that make it unnecessary to inherit from vec_iterator?

		protected:
			iterator_type	m_it;
		public:
			reverse_iterator(void): m_it() {}
			explicit reverse_iterator (iterator_type it): m_it(it){}

			//TODO://wie sieht das nochmal ausgeschrieben aus?
			template <class value_type>  reverse_iterator (const reverse_iterator<value_type>& rev_it): m_it(rev_it.base()){}
			//constructoren wollen die priv_memeber direkt und nicht per getter function!
			~reverse_iterator(void) {}
			//good practice
    		iterator_type				base() const {return this->m_it;}
			reference 					operator*() const {iterator_type tmp = this->base(); return *(--tmp);}
			pointer						operator->() const {return &(operator*());}
    		reverse_iterator  			operator+(difference_type n) const {return reverse_iterator(this->m_it - n);}
  			reverse_iterator& 			operator++() {--this->m_it;return *this;}
  			reverse_iterator 			operator++(int) {reverse_iterator tmp = *this; --(this->m_it); return tmp;}//post operator//returns a copy of the it, bc the object in place should not be modified
			reverse_iterator& 			operator--() {++this->m_it;return *this;}
  			reverse_iterator 			operator--(int) {reverse_iterator tmp = *this; ++(this->m_it); return tmp;}
			reverse_iterator& 			operator+=(difference_type n) {this->m_it -= n; return *this;}
			reverse_iterator& 			operator-=(difference_type n) {this->m_it += n; return *this;}
    		reverse_iterator 			operator-(difference_type n) const {return reverse_iterator(this->m_it + n);}
			reference 					operator[](difference_type n) {return *(*this + n);}//complicated... mal's mal auf!
			template <class Iterator1, class Iterator2>
			friend bool					operator==(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() == r.base();}
			template <class Iterator1, class Iterator2>
			friend bool					operator!=(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() != r.base();}
			template <class Iterator1, class Iterator2>
			friend bool					operator>(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() < r.base();}
			template <class Iterator1, class Iterator2>
			friend bool					operator>=(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() <= r.base();}
			template <class Iterator1, class Iterator2>
			friend bool					operator<(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() > r.base();}
			template <class Iterator1, class Iterator2>
			friend bool					operator<=(const reverse_iterator<Iterator1> l, const reverse_iterator<Iterator2> r) {return l.base() >= r.base();}
			//correct?
			template <class Iterator>
			difference_type		operator-(const reverse_iterator<Iterator> other) {return other.m_it - this->m_it; }


	};
	template< class IT >
	reverse_iterator<IT>				operator+(typename reverse_iterator<IT>::difference_type n, const reverse_iterator<IT> &rev_it) {return reverse_iterator<IT>(rev_it.base() - n);}
	//TODO:muss geerbt werden, reicht der constructor aus?
	//TODO:teste damit dus's verstehst!
}
