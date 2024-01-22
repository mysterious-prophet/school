#include <utility>
#include <iostream>
#include <string>
using namespace std;

using namespace std;

template<typename T>
concept he�ovateln� = requires(T a)
{
	{std::hash<T>{}(a)} -> std::convertible_to<std::size_t>;
};

template<int N>
concept sud� = N % 2 == 0;

template<class T>
struct he�ovadlo
{
	static inline size_t k�d(T t)
	{
		return hash<string>{}(string{ typeid(t).name() });
	}
};

template<class T> requires he�ovateln�<T>
struct he�ovadlo<T>
{
	static inline size_t k�d(T t)
	{
		return hash<T>{}(t);
	}
};

template<class T> 
size_t he�ov�_k�d(T t)
{
	return he�ovadlo<T>::k�d(t);
}

class X{};

// -----

template<int N>
struct hodnota
{
	static const int v�sledek = N;
};

template<int N> requires //sud�<N>
                          (N % 2 == 0)  // Znamen� tot�
struct hodnota<N>
{
	static const int v�sledek = N + 1;
};


int main()
{
	cout << he�ov�_k�d(55) << endl;
	cout << he�ov�_k�d(X{}) << endl;
	cout << hodnota<6>::v�sledek << endl;
}