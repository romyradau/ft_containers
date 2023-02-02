#ifndef __FT_TYPE_TRAITS_HPP_
# define __FT_TYPE_TRAITS_HPP_

namespace ft { // NAMESPACE FT

/* ------------------------------- ENABLE IF -------------------------------- */
/* 
If B is true, std::enable_if has a public member typedef type, equal to T;
otherwise, there is no member typedef.
*/

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if <true, T> {
	typedef T type;
};

/* ------------------------------ IS INTEGRAL ------------------------------- */
/*
Checks whether T is an integral type. Provides the member constant value
which is equal to true, if T is the type bool, char, char8_t (since C++20),
char16_t, char32_t, wchar_t, short, int, long, long long, or any
implementation-defined extended integer types, including any signed,
unsigned, and cv-qualified variants. Otherwise, value is equal to false.
*/

template <bool __v = true>
struct bool_constant {
	static const bool value = __v;
	typedef bool			value_type;
	typedef bool_constant	type;
};


typedef bool_constant <true>	true_type;
typedef bool_constant <false>	false_type;


template <class T> struct __ft_is_integral						: public false_type {};
		
template < > struct __ft_is_integral <bool>						: public true_type {};
template < > struct __ft_is_integral <char>						: public true_type {};
template < > struct __ft_is_integral <char16_t>					: public true_type {};
template < > struct __ft_is_integral <char32_t>					: public true_type {};
template < > struct __ft_is_integral <wchar_t>					: public true_type {};
template < > struct __ft_is_integral <signed char>				: public true_type {};
template < > struct __ft_is_integral <short int>				: public true_type {};
template < > struct __ft_is_integral <int>						: public true_type {};
template < > struct __ft_is_integral <long int>					: public true_type {};
template < > struct __ft_is_integral <unsigned char>			: public true_type {};
template < > struct __ft_is_integral <unsigned short int>		: public true_type {};
template < > struct __ft_is_integral <unsigned int>				: public true_type {};
template < > struct __ft_is_integral <unsigned long int>		: public true_type {};

// is_integral:
template <typename T>
class is_integral : public __ft_is_integral< T > {};

/* ------------------------------------------------------------------------ */

} // NAMESPACE FT

#endif // __FT_TYPE_TRAITS_HPP_