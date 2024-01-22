#include <utility>
#include <iostream>
#include <string>
using namespace std;

using namespace std;

template<typename T>
concept hešovatelný = requires(T a)
{
	{std::hash<T>{}(a)} -> std::convertible_to<std::size_t>;
};

template<int N>
concept sudé = N % 2 == 0;

template<class T>
struct hešovadlo
{
	static inline size_t kód(T t)
	{
		return hash<string>{}(string{ typeid(t).name() });
	}
};

template<class T> requires hešovatelný<T>
struct hešovadlo<T>
{
	static inline size_t kód(T t)
	{
		return hash<T>{}(t);
	}
};

template<class T> 
size_t hešový_kód(T t)
{
	return hešovadlo<T>::kód(t);
}

class X{};

// -----

template<int N>
struct hodnota
{
	static const int výsledek = N;
};

template<int N> requires //sudé<N>
                          (N % 2 == 0)  // Znamená totéž
struct hodnota<N>
{
	static const int výsledek = N + 1;
};


int main()
{
	cout << hešový_kód(55) << endl;
	cout << hešový_kód(X{}) << endl;
	cout << hodnota<6>::výsledek << endl;
}