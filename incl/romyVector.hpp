#pragma once

#include <iostream>
#include <memory>
//for std::allocator
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <iterator>

namespace ft{}
using namespace ft;
//geht das so oder muss ich's normal eingliedern?

//The typedef-names are aliases for existing types, and are not declarations of new types.
template<typename T, class Alloc = std::allocator<T>>
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
	typedef ft::vec_iterator<value_type>		iterator;
	typedef ft::vec_iterator<const value_type>	const_iterator;
	typedef	ft::vec_iterator<value_type>		reverse_iterator;
	typedef ft::vec_iterator<const value_type>	const_reverse_iterator;

	// difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type
	// will be in iterator traits

	//non-members, how does one know them??
	private:
		size_type								_cap; //avaialble space
		size_type								_size; //actual space
		allocator_type							_alloc; //allocator object used by vector
		pointer									_pointer; //pointer to vector

	public:
		explicit Vector (const allocator_type& alloc = allocator_type());
		explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		//TODO: den vielleicht erst nach IteratorImplementierung?
		template <class InputIterator>         Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		Vector (const vector& x);

		Vector& operator= (const vector& x);
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
}

//Constructs a container with n elements. Each element is a copy of val.
//mit value_type() ist T vom vector gemeint == hier werden z.b. 5, int allociert
template<typename T, class Alloc>
Vector<T, Alloc>::Vector(size_type n, const value_type& val, const allocator_type &alloc){
	_cap = n;//TODO: sollte das hier nicht mehr sein, von Anfang an?
	_size = n;	
	_alloc = alloc; //inbuilt it knows that it looks for std::allocator<T>
	_pointer = this->_alloc.allocate(n); // allocated aber nicht constructed
	for (size_t i = 0; i < n; i++)
		this->_alloc.construct(_pointer + i, val);
}

//shallow copy constructor
template<typename T, class Alloc>
Vector<T, Alloc>::Vector(const vector& x){
	_cap = 0;
	_size = 0;
	_alloc = std::allocator<T>;
	_pointer = NULL;
	*this = x;
	//TODO: warum muss erstmal leer initialisiert werden
}

//ASSIGN CONTENT
//TODO::warum muss man immer den spezifischen vektor angeben??vector<T, Alloc
template<typename T, class Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector<T, Alloc>& x){
	
}

//VECTOR DESTRUCTOR
template<typename T, class Alloc>
Vector<T, Alloc>::~Vector(){
	for(size_t i = 0; i < this->_size; i++)
		this->_alloc.destroy(&this->_pointer[i]); //destroyed aber noch nicht deallocated
	this->_alloc.deallocate(this->_pointer, this->_capacity); // braucht kein [], deallocated so viele items wie einsta allocated
}


// template<typename T>
// class Vector
// {
// 	public:
// 		Vector(){
// 			ReAlloc(2);
// 		}
// 		//wie wird in STL allociert?
// 		~Vector(){
// 			delete [] m_Data;
// 			//also make sure to delete the pointers?
// 			//loscht nicht die elemente sondern ???
// 		}

// 		void PushBack(const T& value){
// 			if (m_Size >= m_Capacity)//why not just >
// 				ReAlloc(m_Capacity + m_Capacity / 2);
// 			m_Data[m_Size] = value;
// 			m_Size++;
// 		}

// 		void PopBack(){
// 			if (m_Size > 0){
// 				m_Size--;
// 				m_Data[m_Size].~T();//calls the explicit deconstructor of the type
// 			}
// 		}

// 		void Clear(){
// 			for(size_t i = 0; i < m_Size; i++)
// 				m_Data[i].~T();
// 		}
		
// 		T const & operator[] (size_t index) const{
// 			return m_Data[index];
// 			//TODO:check what STL does if index is not available!
// 		}
// 		//access a vector element via a pointer, which already has the [ operator ]
// 		//readOnly
		
// 		T& operator[] (size_t index){
// 			return m_Data[index];
// 		}
// 		//readAndWrite

// 		size_t Size() const{
// 			return m_Size;
// 		}

// 	private:
// 		void ReAlloc(size_t newCapacity){

// 			T* newVector = new T[newCapacity];
// 			//warum muss man fuer weniger space trotzdem allocieren?

// 			if (newCapacity < m_Size)
// 				m_Size = newCapacity;
				
// 			//will be changed to cumstom allocator here
// 			for (size_t i = 0; i < m_Size; i++){
// 				newVector[i] = m_Data[i];
// 				//this is copying -> moving would be better
// 			}
// 			delete [] m_Data;
// 			m_Data = newVector;
// 			m_Capacity = newCapacity;
// 		}

// 	private:
// 		T* 		m_Data = nullptr;

// 		size_t	m_Size = 0;
// 		size_t	m_Capacity = 0;
// };