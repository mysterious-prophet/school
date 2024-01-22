#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
class je_to_tøída
{
	using ano = char[1];
	using ne = char[2];
	template<typename C> static ano& test(int C::*);
	template<typename C> static ne& test(...);

public:
	static constexpr bool výsledek = sizeof(test<T>(0)) == sizeof(ano);
};

template<typename T>
constexpr bool je_to_tøída_v = je_to_tøída<T>::výsledek;

struct A{};
class B {};
union C{};
enum struct D{jedna, dva};

template<typename T>
void výpis()
{
	cout << boolalpha;
	cout << "Typ: " << typeid(T).name() << " je tøídou: " << je_to_tøída_v<T> << endl;
}

int main()
{
	system("CHCP 1250 > NUL");
	výpis<A>();
	výpis<B>();
	výpis<C>();
	výpis<D>();
	výpis<char>();
}