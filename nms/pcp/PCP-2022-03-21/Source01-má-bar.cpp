#include <iostream>
#include <type_traits>
#include <utility>

using namespace std;

template<class T>
struct má_bar
{
private:
	template<class C> static auto test(int) -> decltype(C::bar, 1);
	template<class C> static char test(...);
public:
	static constexpr bool výsledek = sizeof(test<T>(0)) == sizeof(int);
};

template<class T>
constexpr bool má_bar_v = má_bar<T>::výsledek;

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
//constexpr bool má_bar_int = má_bar<T>::výsledek && je_int<decltype(T::bar)>::value;

template<class T>
constexpr bool má_bar_int()
{
	if constexpr (má_bar_v<T>)
	{
		return je_int<decltype(T::bar)>::value;
	}
	else
	{
		return false;
	}
}

template<class T>
struct má_rovnost
{
private:
	template<class C> static auto test(int)->decltype(declval<C&>() == declval<C&>(), 1);
	template<class C> static char test(...);
public:
	static constexpr bool výsledek = sizeof(test<T>(0)) == sizeof(int);
};

template<class T>
constexpr bool má_rovnost_v = má_rovnost<T>::výsledek;

int main()
{
	cout << boolalpha;
	cout << má_bar_v<X> << endl << má_bar_v<Y> << endl;
	cout << je_int_v<int> << endl << je_int_v<long> << endl;
	cout << "----------" << endl;
	//cout << má_bar_int<X> << endl << má_bar_int<Y> << endl << má_bar_int<long> << endl;
	cout << má_bar_int<X>() << endl << má_bar_int<Y>() << endl << má_bar_int<long>() << endl;
	cout << má_rovnost_v<int> << endl;
	cout << má_rovnost_v<X> << endl;
}