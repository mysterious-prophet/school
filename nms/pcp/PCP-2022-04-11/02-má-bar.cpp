#include <type_traits>
#include <iostream>

using namespace std;

template<class T>
class má_bar
{
	static const int ANO = 1;
	static const char NE = 'a';
	template<class C> static auto test(int) -> decltype(C::bar, ANO);
	template<class C> static auto test(...) -> decltype(NE);
public:
	static const bool výsledek = (sizeof(test<T>(0)) == sizeof(ANO));
};

template<class T>
static constexpr bool má_bar_v = má_bar<T>::výsledek;

template<class T>
struct je_to_int: false_type{};

template<>
struct je_to_int<int> : true_type {};

template<class T>
static constexpr bool je_to_int_v = je_to_int<T>::value;

template<class T>
constexpr bool má_bar_int_f()
{
	if constexpr (má_bar_v<T>)
	{
		return je_to_int_v<decay_t<decltype(T::bar)>>;
	}
	else
	{
		return false;
	}
}

struct X{};
struct Y { int bar; };
class Z { int bar; };


template<class T, bool hodnota>
struct má_bar_int_impl: false_type{};

template<class T>
struct má_bar_int_impl<T, true>
{
	static constexpr bool value = je_to_int_v<decltype(T::bar)>;
};

template<class T>
struct má_bar_int_m
{
	static constexpr bool výsledek = má_bar_int_impl<T, má_bar_v<T>>::value;
};

template<class T>
static constexpr bool má_bar_int_m_v = má_bar_int_m<T>::výsledek;

template<class T>
concept je_int = je_to_int_v<T>;

template<class T>
concept má_bar_int_c = requires
{
	{T::bar};
} && je_int<decltype(T::bar)>;


int main()
{
	cout << boolalpha;
	/*cout << má_bar_int_f<X>() << endl;
	cout << má_bar_int_f<Y>() << endl;
	cout << má_bar_int_f<Z>() << endl;
	cout << má_bar_int_f<int>() << endl;*/
	/*cout << má_bar_int_m_v<X> << endl;
	cout << má_bar_int_m_v<Y> << endl;
	cout << má_bar_int_m_v<Z> << endl;
	cout << má_bar_int_m_v<int> << endl;*/
	cout << má_bar_int_c<X> << endl;
	cout << má_bar_int_c<Y> << endl;
	cout << má_bar_int_c<Z> << endl;
	cout << má_bar_int_c<int> << endl;
}