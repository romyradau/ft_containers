#pragma once
#include <iostream>
#include "avl_tree.hpp"
#include "pair.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include <stdexcept>

namespace ft{



// map<int, char, std::greater<int>, my_allocaotor >
// Allocator = my_allocator

template<
	class Key,
    class T,
    class Compare = std::less<Key>,//überall wo im code Compare steht, paste std::lesss rein
    class Allocator = std::allocator<ft::pair<const Key, T> > >//man kann nur den value nicht den key verandern
	//es ist nur std::allocator<ft::pair<const Key, T>> falls jdm nichts reingibt
	
	class map{

		
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef	ft::pair<const Key, T> 					value_type;
			typedef	std::size_t								size_type;
			typedef	std::ptrdiff_t							difference_type;
			typedef	Compare									key_compare; //https://en.cppreference.com/w/cpp/utility/functional/less
			typedef	Allocator								allocator_type;
			typedef value_type&								reference;
			typedef	const value_type&						const_reference;
			typedef	typename Allocator::pointer				pointer;//pointer zum pair
			typedef	typename Allocator::const_pointer		const_pointer;
			typedef	ft::map_iterator<value_type>			iterator;
			typedef	ft::map_iterator<const value_type>		const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;


			class value_compare{
			protected:
			  Compare comp;
			public:
			  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			  typedef bool result_type;
			  typedef value_type first_argument_type;
			  typedef value_type second_argument_type;
			  bool operator() (const value_type& x, const value_type& y) const{return comp(x.first, y.first);}
			  bool operator()(const key_type& key, const value_type &y) const { return comp(key, y.first); }
              bool operator()(const value_type &x, const key_type& key) const { return comp(x.first, key); }
			};

			typedef ft::avl_tree<key_type, mapped_type, value_compare, allocator_type>		avl_tree;
			typedef	typename avl_tree::node_pointer	node_pointer;
			typedef	typename avl_tree::node			node;

		private:
			avl_tree										_avl;
			// allocator_type														_alloc;
			// typename Allocator::template rebind <ft::node<value_type> >::other	_node_alloc;
			//beim allocator den template type asugewechselt
			//other ist ein allocator auf diesen type

		public:

			// map(): avl(){};
			~map(){};//This destroys all container elements, and deallocates all the storage capacity allocated by the map container using its allocator.
			
			// empty (1)
			//comp = ein objekt mit dem ich die keys von den pairs vergleiche
			//alloc = das was das pair allociert
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _avl(comp, alloc) {

			}
			//_avl() simply calls the empty constructor

			// range (2)
			// einfuegen von werten einer bereits bestehenden map
			//comp und alloc werden hier nru mitgegeben, damit man die dem tree/der node weiter geben kann.
			template <class InputIterator>  map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _avl(comp, alloc){
				while(first != last){
					insert(*first);
					first++;
				}

			}

			// copy (3)
			// deep copy von einer bestehenden map
			map (const map& other): avl_tree(other._avl){}

			map& operator= (const map& x){
				if (this != &x)
					this->_avl = x->_avl;
				return *this;
			}

			iterator			begin(){if (_avl.getRoot()) return (iterator(_avl.min_node(_avl.getRoot()))); return this->end();}
			const_iterator			begin()const {if (_avl.getRoot()) return (iterator(_avl.min_node(_avl.getRoot()))); return this->end();}//durch den cast im map_iterator wird heir const zurueckgegeben
			iterator			end(){return iterator(_avl.max_node( _avl.getRoot())->right);}
			const_iterator			end()const {return iterator(_avl.max_node( _avl.getRoot())->right);}//durch den cast im map_iterator wird heir const zurueckgegeben
			reverse_iterator	rbegin(){if (empty()) return rend(); return reverse_iterator(end());}
			const_reverse_iterator	rbegin()const {if (empty()) return rend(); return const_reverse_iterator(end());}
			reverse_iterator	rend(){return reverse_iterator(begin());}
			const_reverse_iterator	rend()const{return const_reverse_iterator(begin());}

			// single element (1)	
			ft::pair<iterator,bool> insert (const value_type& val){


				return (_avl.insert(val));
			}

			// with hint (2)	
			iterator insert (iterator position, const value_type& val){
				(void)position;
				ft::pair<iterator,bool> it = _avl.insert(val);
				return it.first;
			}

			// range (3)	
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last){

				for(;first != last; first++)
					insert(*first);

			}

			value_compare	value_comp() const {
				return value_compare();
			}



			mapped_type& operator[] (const key_type& k){
				ft::pair<iterator, bool> mapped = insert(value_type(k, mapped_type()));
				return (mapped.first->second);
			}

			mapped_type& at (const key_type& k){

				node_pointer success = this->_avl.searchKey(_avl.getRoot(), k);
				if (success)
					return success->data.second;
				else
					throw std::out_of_range("no matching key");
			}

			const mapped_type& at (const key_type& k) const{

				node_pointer success = this->_avl.searchKey(_avl.getRoot(), k);
				if (success)
					return success->data.second;
				else
					throw std::out_of_range("no matching key");
			}

			bool empty() const{
				if (begin() == end())
					return true;
				return false;
			}

			void printMap() const { this->_avl.printTree(); }

	};

		

}