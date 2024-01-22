#include <iostream>
#include <type_traits>
#include <utility>

using namespace std;

template<class T>
struct m�_bar
{
private:
	template<class C> static auto test(int) -> decltype(C::bar, 1);
	template<class C> static char test(...);
public:
	static constexpr bool v�sledek = sizeof(test<T>(0)) == sizeof(int);
};

template<class T>
constexpr bool m�_bar_v = m�_bar<T>::v�sledek;

struct X{};
struct Y
{
	int bar;
};

struct Z
{
	long bar;
};

template<class T>
struct je_int : false_type {};

template<>
struct je_int<int>: true_type{};

template<class T>
constexpr bool je_int_v = je_int<T>::value;

//template<class T>
//constexpr bool m�_bar_int = m�_bar<T>::v�sledek && je_int<decltype(T::bar)>::value;

template<class T>
constexpr bool m�_bar_int()
{
	if constexpr (m�_bar_v<T>)
	{
		return je_int<decltype(T::bar)>::value;
	}
	else
	{
		return false;
	}
}

template<class T>
struct m�_rovnost
{
private:
	template<class C> static auto test(int)->decltype(declval<C&>() == declval<C&>(), 1);
	template<class C> static char test(...);
public:
	static constexpr bool v�sledek = sizeof(test<T>(0)) == sizeof(int);
};

template<class T>
constexpr bool m�_rovnost_v = m�_rovnost<T>::v�sledek;

int main()
{
	cout << boolalpha;
	cout << m�_bar_v<X> << endl << m�_bar_v<Y> << endl;
	cout << je_int_v<int> << endl << je_int_v<long> << endl;
	cout << "----------" << endl;
	//cout << m�_bar_int<X> << endl << m�_bar_int<Y> << endl << m�_bar_int<long> << endl;
	cout << m�_bar_int<X>() << endl << m�_bar_int<Y>() << endl << m�_bar_int<long>() << endl;
	cout << m�_rovnost_v<int> << endl;
	cout << m�_rovnost_v<X> << endl;
}