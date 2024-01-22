#include <iostream>
#include <utility>
#include <concepts>

using namespace std;

template<typename T>
concept he�ovateln� = requires(T a)
{
	{std::hash<T>{}(a)} -> std::convertible_to<std::size_t>;
};

template<class T> requires he�ovateln�<T>
auto f(T a)
{
	return std::hash<T>{}(a);
}

/* template<class T>
auto f(T a)
{
	return std::hash<T>{}(a);
}*/

template<class T> 
auto f1(T a) requires he�ovateln�<T>
{
	return std::hash<T>{}(a);
}

template<typename T, typename U> requires he�ovateln�<T> && he�ovateln�<U>
struct n�stroj
{
	// ...
};


template<he�ovateln� T>
auto f2(T a)
{
	return std::hash<T>{}(a);
}

template<he�ovateln� T, he�ovateln� U>
struct n�stroj1
{
	// ...
};

size_t f3(he�ovateln� auto s)
{
	return hash<decltype(s)>{}(s);
}

class X{};

template<class T>
size_t pseudohe�(T a)
{
	if constexpr (he�ovateln�<T>)
	{
		return std::hash<T>{}(a);
	}
	else
	{
		return std::hash<std::string>{}(std::string(typeid(T).name()));
	}
}


int main()
{
	auto text = "nazdar"s;
	cout << f(text) << endl;
	//cout << f(X{}) << endl;
	auto x = pseudohe�(7);
	pseudohe�(X{});

}