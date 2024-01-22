#include <iostream>
#include <utility>
#include <concepts>

using namespace std;

template<typename T>
concept hešovatelný = requires(T a)
{
	{std::hash<T>{}(a)} -> std::convertible_to<std::size_t>;
};

template<class T> requires hešovatelný<T>
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
auto f1(T a) requires hešovatelný<T>
{
	return std::hash<T>{}(a);
}

template<typename T, typename U> requires hešovatelný<T> && hešovatelný<U>
struct nástroj
{
	// ...
};


template<hešovatelný T>
auto f2(T a)
{
	return std::hash<T>{}(a);
}

template<hešovatelný T, hešovatelný U>
struct nástroj1
{
	// ...
};

size_t f3(hešovatelný auto s)
{
	return hash<decltype(s)>{}(s);
}

class X{};

template<class T>
size_t pseudoheš(T a)
{
	if constexpr (hešovatelný<T>)
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
	auto x = pseudoheš(7);
	pseudoheš(X{});

}