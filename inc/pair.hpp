#pragma once

namespace ft {

template <class T1, class T2>
struct pair {
		typedef	T1								first_type;
		typedef T2								second_type;
		typedef pair<first_type, second_type>	value_type;

		T1 first;
		T2 second;

		pair(): first(first_type()), second(second_type()) {}
		pair(const value_type& pr): first(pr.first), second(pr.second) {}
		pair(const first_type& a, const second_type& b): first(a), second(b) {}
		~pair() {}

		pair& operator=(const pair& pr) {
			if (this != &pr) {
				this->first = pr.first;
				this->second = pr.second;
			}
			return (*this);
		}
		friend std::ostream& operator<<(std::ostream& stream, const pair& pr) {
			stream << pr.first << ": " << pr.second;
			return (stream);
		}
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

template <class T1, class T2>  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return ((lhs.first == rhs.first) && (lhs.second == rhs.second)); }
template <class T1, class T2>  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }
template <class T1, class T2>  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return ((lhs.first < rhs.first) && (lhs.second < rhs.second)); }
template <class T1, class T2>  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }
template <class T1, class T2>  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (rhs < lhs); }
template <class T1, class T2>  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }
//ist das vollstaendig?
}
