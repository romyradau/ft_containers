#pragma once

//iterator_traits is a template class that contains nothing but nested typedefs
//struct is by default all public whereas class is by default all private
namespace ft{
	template <class IT>
	struct iterator_traits {
	typedef typename IT::iterator_category iterator_category;//iterator tag
	typedef typename IT::value_type        value_type;// the type of object that the iterator points to
	typedef typename IT::difference_type   difference_type;//a signed integral type that can be used to represent the distance between two iterators
	typedef typename IT::pointer           pointer;
	typedef typename IT::reference         reference;
	};
	//a fully generic one

	template <class T>
	struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag iterator_category;
	typedef T                          		value_type;
	typedef ptrdiff_t                 		difference_type;
	typedef T*                         		pointer;
	typedef T&                         		reference;
	};
	//a specialization that is used whenever the template argument is a pointer type

	template <class T>
	struct iterator_traits<T const *> {
	typedef std::random_access_iterator_tag iterator_category;
	typedef T                          		value_type;
	typedef ptrdiff_t                  		difference_type;
	typedef T const *                       pointer;
	typedef T const &                       reference;
	};

}