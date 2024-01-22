#include <type_traits>
#include <iostream>

using namespace std;

template<class T>
class m�_bar
{
	static const int ANO = 1;
	static const char NE = 'a';
	template<class C> static auto test(int) -> decltype(C::bar, ANO);
	template<class C> static auto test(...) -> decltype(NE);
public:
	static const bool v�sledek = (sizeof(test<T>(0)) == sizeof(ANO));
};

template<class T>
static constexpr bool m�_bar_v = m�_bar<T>::v�sledek;

template<class T>
struct je_to_int: false_type{};

template<>
struct je_to_int<int> : true_type {};

template<class T>
static constexpr bool je_to_int_v = je_to_int<T>::value;

template<class T>
constexpr bool m�_bar_int_f()
{
	if constexpr (m�_bar_v<T>)
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
struct m�_bar_int_impl: false_type{};

template<class T>
struct m�_bar_int_impl<T, true>
{
	static constexpr bool value = je_to_int_v<decltype(T::bar)>;
};

template<class T>
struct m�_bar_int_m
{
	static constexpr bool v�sledek = m�_bar_int_impl<T, m�_bar_v<T>>::value;
};

template<class T>
static constexpr bool m�_bar_int_m_v = m�_bar_int_m<T>::v�sledek;

template<class T>
concept je_int = je_to_int_v<T>;

template<class T>
concept m�_bar_int_c = requires
{
	{T::bar};
} && je_int<decltype(T::bar)>;


int main()
{
	cout << boolalpha;
	/*cout << m�_bar_int_f<X>() << endl;
	cout << m�_bar_int_f<Y>() << endl;
	cout << m�_bar_int_f<Z>() << endl;
	cout << m�_bar_int_f<int>() << endl;*/
	/*cout << m�_bar_int_m_v<X> << endl;
	cout << m�_bar_int_m_v<Y> << endl;
	cout << m�_bar_int_m_v<Z> << endl;
	cout << m�_bar_int_m_v<int> << endl;*/
	cout << m�_bar_int_c<X> << endl;
	cout << m�_bar_int_c<Y> << endl;
	cout << m�_bar_int_c<Z> << endl;
	cout << m�_bar_int_c<int> << endl;
}