#ifndef __SEZNAM_H__
#define __SEZNAM_H__

#include <memory>
#include "seznam_impl.h"

template<class T, 
	template<class T> class Alok�tor = std::allocator,
	class Implementace = seznam_impl<T, Alok�tor>
>
class seznam
{
	Implementace *u_seznam;
public:
	// Zve�ej�ovan� datov� typy
	using typ_hodnot = typename Implementace::typ_hodnot;
	using iter�tor_seznamu = typename Implementace::iter�tor_seznamu;
	using konstantn�_iter�tor_seznamu = typename Implementace::konstantn�_iter�tor_seznamu;
	// Konstruktory a destruktor
	seznam() { u_seznam = new Implementace(); }
	seznam(std::initializer_list<T> seznam_inicializ�tor�);
	seznam(const seznam& s) { u_seznam = new Implementace(*(s.u_seznam)); }
	seznam(seznam&& s) : seznam() {	proho�(s); }
	~seznam() { delete u_seznam; }
	// P�i�azov�n�
	seznam& operator = (const seznam& s) { *(this->u_seznam) = *(s.u_seznam); return *this;	}
	seznam& operator = (seznam&& s) { proho�(s); return *this; }
	// Stav seznamu
	bool pr�zdn�() const noexcept { return u_seznam->pr�zdn�(); }
	std::size_t velikost() const noexcept { return u_seznam->velikost(); }
	// P��stup k prvk�m
	typ_hodnot prvn�() { return u_seznam->prvn�(); }
	iter�tor_seznamu najdi(const T co) { return u_seznam->najdi(co); }
	// Vkl�d�n� do seznamu
	void vlo�_na_konec(const typ_hodnot &co){ u_seznam->vlo�_na_konec(co); }
	void vlo�_na_konec(typ_hodnot &&co) { u_seznam->vlo�_na_konec(co); }
	void vlo�_na_za��tek(const typ_hodnot& co) { u_seznam->vlo�_na_za��tek(co); }
	void vlo�_na_za��tek(typ_hodnot&& co) { u_seznam->vlo�_na_za��tek(std::move(co)); }
	iter�tor_seznamu vlo�_za(iter�tor_seznamu kam, T& co) { return u_seznam->vlo�_za(kam, co); }
	iter�tor_seznamu vlo�_za(iter�tor_seznamu kam, T&& co) { return u_seznam->vlo�_za(kam, std::move(co)); }
	// Ostra�ov�n�
	void odstra�_prvn�() { u_seznam->odstra�_prvn�(); }
	iter�tor_seznamu odstra�(iter�tor_seznamu ten) { return u_seznam->odstra�(ten); }
	void vypr�zdni() { u_seznam->vypr�zdni(); }
	// Pro lad�n�
	void vypi�() { u_seznam->vypi�(); }
	// Prohozen� obsahu dvou seznam�
	void proho�(seznam &s) { std::swap(u_seznam, s.u_seznam); }
	// Iter�tory
	iter�tor_seznamu begin() noexcept { return u_seznam->begin(); };
	konstantn�_iter�tor_seznamu begin() const noexcept { return u_seznam->begin(); };
	konstantn�_iter�tor_seznamu cbegin() const noexcept { return u_seznam->cbegin(); };
	iter�tor_seznamu end() noexcept { return u_seznam->end(); };
	konstantn�_iter�tor_seznamu end() const noexcept { return u_seznam->end(); };
	konstantn�_iter�tor_seznamu cend() const noexcept { return u_seznam->cend(); };
	// Spojov�n� seznam�
	seznam operator+(seznam& s) &;
	seznam operator+(seznam&& s) &;
	seznam operator+(seznam& s) &&;
	seznam operator+(seznam&& s) &&;
	seznam operator+=(seznam& s) { *u_seznam += *s.u_seznam; return *this; }
	seznam operator+=(seznam&& s) { *u_seznam += std::move(*s.u_seznam); return *this; }
private:
	seznam(Implementace* impl): u_seznam(impl){}
	template<bool lev�_r_hodnota, bool prav�_r_hodnota>
	seznam oper�tor_plus_impl(seznam& a);
};

template<class T, template<class T> class Alok�tor, class Implementace>
template<bool lev�_r_hodnota, bool prav�_r_hodnota>
seznam<T, Alok�tor, Implementace>
seznam<T, Alok�tor, Implementace>::oper�tor_plus_impl(seznam& a)
{
	seznam<T, Alok�tor, Implementace> v�sledek;
	Implementace pom;
	if constexpr (!lev�_r_hodnota && !prav�_r_hodnota)
	{
		pom = *u_seznam + *a.u_seznam;
	}
	else if constexpr (!lev�_r_hodnota && prav�_r_hodnota)
	{
		pom = *u_seznam + std::move(*a.u_seznam);
	}
	else if constexpr (lev�_r_hodnota && !prav�_r_hodnota)
	{
		pom = std::move(*u_seznam) + *a.u_seznam;
	}
	else
	{
		pom = std::move(*u_seznam) + std::move(*a.u_seznam);
	}
	v�sledek.u_seznam->proho�(pom);
	return v�sledek;
}

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace>::seznam(std::initializer_list<T> seznam_inicializ�tor�)
{
	u_seznam = new seznam_impl<T, Alok�tor>(seznam_inicializ�tor�);
}

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace> seznam<T, Alok�tor, Implementace>::operator+(seznam & s) &
{
	return oper�tor_plus_impl<false, false>(s);
}

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace> seznam<T, Alok�tor, Implementace>::operator+(seznam && s) &
{
	return oper�tor_plus_impl<false, true>(s);
}

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace> seznam<T, Alok�tor, Implementace>::operator+(seznam & s) &&
{
	return oper�tor_plus_impl<true, false>(s);
}

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace> seznam<T, Alok�tor, Implementace>::operator+(seznam && s) &&
{
	return oper�tor_plus_impl<true, true>(s);
}
#endif //__SEZNAM_H__
