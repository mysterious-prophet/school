#include <type_traits>
#include <utility>
#include <iostream>

// Zjišuje, zda má typ T vnoøenı veøejnì pøístupnı typ jménem "typ"
template<class, class = std::void_t<> >
struct má_vnoøenı_typ : std::false_type
{ };

template<class T>
struct má_vnoøenı_typ< T, std::void_t<typename T::typ> > : std::true_type
{
};

template<class T>
constexpr bool má_vnoøenı_typ_v = má_vnoøenı_typ<T>::value;


// Pro otestování
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

// Zjišuje, zda má typ T veøejnì pøístupnı prefixovı operátor ++

// Primární šablona pro typy, které ho nemají
template<class T, class = std::void_t<> >
struct má_preinkrement : std::false_type
{ };

// Specializace pro typy, které ho mají
template<class T>
struct má_preinkrement < T, std::void_t<decltype(++std::declval<T&>())>> : std::true_type
{};

template<class T>
constexpr bool má_preinkrement_v = má_preinkrement<T>::value;


// Pro testování
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
	std::cout << má_vnoøenı_typ_v<X> << std::endl;
	std::cout << má_vnoøenı_typ_v<Y> << std::endl;
	std::cout << má_vnoøenı_typ_v<Z> << std::endl;

	std::cout << má_preinkrement_v<Numero> << std::endl;
	std::cout << má_preinkrement_v<Numero2> << std::endl;
}