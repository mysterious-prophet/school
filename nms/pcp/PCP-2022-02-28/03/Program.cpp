#include <stdarg.h>
#include <iostream>
#include <array>
#include <type_traits>

using namespace std;

size_t pomoc(size_t n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t výsledek = 0;
	for (size_t i = 0; i < n; i++)
	{
		char c = va_arg(ap, char);
		výsledek = 3 * výsledek + (c - '0');
	}
	va_end(ap);
	return výsledek;
}


template<char ... znaky> int operator ""_t()
{
	return pomoc(sizeof...(znaky), znaky...);
}

// Vytvoøení instance typu array<>

template<typename... Ts>
constexpr auto vytvoø_pole(Ts&&...ts)->std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
	return { forward<Ts>(ts)... };
}

template<typename ... Ts> void f(Ts ... ts) {}

// seznam formálních parametrù šablony
template<typename ... T> struct kontejner
{
	template<T...hodnoty>
	struct nástroje {};
};

// seznam skuteèných parametrù šablony
template<class A, class B, class ... C> 
void fun(A par1, B par2, C ... par3)
{
	kontejner<C..., A, B> t1;
	kontejner<A, B, C...> t2;
}


// Specifikace pøedka, inic. èást konstruktoru
template<class ... Pøísady>
class kompozice : public Pøísady...
{
public:
	kompozice(const Pøísady& ... pøísady) : Pøísady(pøísady)...
	{}
};

// Záchyt lambda-výrazu
template<class ... Param>
void ff(Param ... param)
{
	auto lambda = [&, param...]{ /*return g(param...);*/ };
}

// specifikace výjimek (zrušeno)
template<class ... T>
void fun(int n) throw(T...)
{
	//...
}

// deklarace using
template<typename ... báze>
struct X : báze...
{
	using báze::g...;
};

[[noreturn]]
void funkce()
{
	// ...
}
int main()
{
	cout << 121_t << endl;

	auto b = vytvoø_pole(1.0, 2.0, 3.0);

	
}