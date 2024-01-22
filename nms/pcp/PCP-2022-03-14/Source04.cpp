#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
class je_to_t��da
{
	using ano = char[1];
	using ne = char[2];
	template<typename C> static ano& test(int C::*);
	template<typename C> static ne& test(...);

public:
	static constexpr bool v�sledek = sizeof(test<T>(0)) == sizeof(ano);
};

template<typename T>
constexpr bool je_to_t��da_v = je_to_t��da<T>::v�sledek;

struct A{};
class B {};
union C{};
enum struct D{jedna, dva};

template<typename T>
void v�pis()
{
	cout << boolalpha;
	cout << "Typ: " << typeid(T).name() << " je t��dou: " << je_to_t��da_v<T> << endl;
}

int main()
{
	system("CHCP 1250 > NUL");
	v�pis<A>();
	v�pis<B>();
	v�pis<C>();
	v�pis<D>();
	v�pis<char>();
}