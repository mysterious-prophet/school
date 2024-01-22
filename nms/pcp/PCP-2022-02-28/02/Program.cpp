#include <type_traits>
#include <utility>
#include <iostream>

// Zji��uje, zda m� typ T vno�en� ve�ejn� p��stupn� typ jm�nem "typ"
template<class, class = std::void_t<> >
struct m�_vno�en�_typ : std::false_type
{ };

template<class T>
struct m�_vno�en�_typ< T, std::void_t<typename T::typ> > : std::true_type
{
};

template<class T>
constexpr bool m�_vno�en�_typ_v = m�_vno�en�_typ<T>::value;


// Pro otestov�n�
struct X
{
	using typ = int;
};

struct Y
{
	using type = int;
};

struct Z
{
private:
	using typ = int;
};

// Zji��uje, zda m� typ T ve�ejn� p��stupn� prefixov� oper�tor ++

// Prim�rn� �ablona pro typy, kter� ho nemaj�
template<class T, class = std::void_t<> >
struct m�_preinkrement : std::false_type
{ };

// Specializace pro typy, kter� ho maj�
template<class T>
struct m�_preinkrement < T, std::void_t<decltype(++std::declval<T&>())>> : std::true_type
{};

template<class T>
constexpr bool m�_preinkrement_v = m�_preinkrement<T>::value;


// Pro testov�n�
class Numero
{
	int n;
public:
	Numero(int n) : n(n) {}
	Numero& operator++() { ++n; return *this; }
};

class Numero2
{
	int n;
public:
	Numero2(int n) : n(n) {}
	Numero2 operator++(int) { int a = n; ++n; return Numero2(a); }
};

int main()
{
	std::cout << m�_vno�en�_typ_v<X> << std::endl;
	std::cout << m�_vno�en�_typ_v<Y> << std::endl;
	std::cout << m�_vno�en�_typ_v<Z> << std::endl;

	std::cout << m�_preinkrement_v<Numero> << std::endl;
	std::cout << m�_preinkrement_v<Numero2> << std::endl;
}