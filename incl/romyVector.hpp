#pragma once

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>

template<typename T>
class Vector
{
	public:
		Vector(){
			ReAlloc(2);
		}
		//wie wird in STL allociert?
		~Vector(){
			delete [] m_Data;
			//also make sure to delete the pointers?
			//loscht nicht die elemente sondern ???
		}

		void PushBack(const T& value){
			if (m_Size >= m_Capacity)//why not just >
				ReAlloc(m_Capacity + m_Capacity / 2);
			m_Data[m_Size] = value;
			m_Size++;
		}

		void PopBack(){
			if (m_Size > 0){
				m_Size--;
				m_Data[m_Size].~T();//calls the explicit deconstructor of the type
			}
		}

		void Clear(){
			for(size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();
		}
		
		T const & operator[] (size_t index) const{
			return m_Data[index];
			//TODO:check what STL does if index is not available!
		}
		//access a vector element via a pointer, which already has the [ operator ]
		//readOnly
		
		T& operator[] (size_t index){
			return m_Data[index];
		}
		//readAndWrite

		size_t Size() const{
			return m_Size;
		}

	private:
		void ReAlloc(size_t newCapacity){

			T* newVector = new T[newCapacity];
			//warum muss man fuer weniger space trotzdem allocieren?

			if (newCapacity < m_Size)
				m_Size = newCapacity;
				
			//will be changed to cumstom allocator here
			for (size_t i = 0; i < m_Size; i++){
				newVector[i] = m_Data[i];
				//this is copying -> moving would be better
			}
			delete [] m_Data;
			m_Data = newVector;
			m_Capacity = newCapacity;
		}

	private:
		T* 		m_Data = nullptr;

		size_t	m_Size = 0;
		size_t	m_Capacity = 0;
};