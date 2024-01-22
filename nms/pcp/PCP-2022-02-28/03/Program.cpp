#include <stdarg.h>
#include <iostream>
#include <array>
#include <type_traits>

using namespace std;

size_t pomoc(size_t n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t v�sledek = 0;
	for (size_t i = 0; i < n; i++)
	{
		char c = va_arg(ap, char);
		v�sledek = 3 * v�sledek + (c - '0');
	}
	va_end(ap);
	return v�sledek;
}


template<char ... znaky> int operator ""_t()
{
	return pomoc(sizeof...(znaky), znaky...);
}

// Vytvo�en� instance typu array<>

template<typename... Ts>
constexpr auto vytvo�_pole(Ts&&...ts)->std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
	return { forward<Ts>(ts)... };
}

template<typename ... Ts> void f(Ts ... ts) {}

// seznam form�ln�ch parametr� �ablony
template<typename ... T> struct kontejner
{
	template<T...hodnoty>
	struct n�stroje {};
};

// seznam skute�n�ch parametr� �ablony
template<class A, class B, class ... C> 
void fun(A par1, B par2, C ... par3)
{
	kontejner<C..., A, B> t1;
	kontejner<A, B, C...> t2;
}


// Specifikace p�edka, inic. ��st konstruktoru
template<class ... P��sady>
class kompozice : public P��sady...
{
public:
	kompozice(const P��sady& ... p��sady) : P��sady(p��sady)...
	{}
};

// Z�chyt lambda-v�razu
template<class ... Param>
void ff(Param ... param)
{
	auto lambda = [&, param...]{ /*return g(param...);*/ };
}

// specifikace v�jimek (zru�eno)
template<class ... T>
void fun(int n) throw(T...)
{
	//...
}

// deklarace using
template<typename ... b�ze>
struct X : b�ze...
{
	using b�ze::g...;
};

[[noreturn]]
void funkce()
{
	// ...
}
int main()
{
	cout << 121_t << endl;

	auto b = vytvo�_pole(1.0, 2.0, 3.0);

	
}