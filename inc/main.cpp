#include <iostream>
#include <string>
#include <deque>

#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

// #define PRINTLN(msg)	\
// do {	\
// 	std::cout << __FILE__ << " " << __LINE__ << ": " << (msg) << std::endl;	\
// } while(0)

#define TIME(func)	\
do {	\
	clock_t	t;	\
	t = clock();	\
	func;	\
	t = clock() - t;	\
	double	tt = ((double)t) / CLOCKS_PER_SEC;	\
	printf("%fs\n", tt);	\
} while(0)

// #define CNT (MAX_RAM / (int)sizeof(Buffer))
#define CNT 1000


template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void	testall(int argc, char** argv){

	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "CNT value:" << CNT << std::endl;
	}
	const int seed = atoi(argv[1]);
	srand(seed);
	std::cout << "SEEED: " << seed <<std::endl;
	std::cout << "CNT: " << CNT <<std::endl;


	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < CNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < CNT; i++)
	{
		const int idx = rand() % CNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < CNT; i++)
		{
			const int idx = rand() % CNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < CNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		int access = rand();
		std::cout << "access" << access<< std::endl;
		sum += map_int[access];
		std::cout << "sum" << sum << std::endl;
	}
	std::cout << "before	" << map_int.size() << std::endl;
	map_int.erase(map_int.begin(), map_int.end());
	std::cout << "after	" << map_int.size() << std::endl;
	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	TIME(testall(argc, argv));
	return (0);
}
