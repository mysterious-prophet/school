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
	seznam(const seznam& s) { u_seznam = new seznam_impl(*(s.u_seznam)); }
	/* Kdybych cht�l zak�zat kop�rov�n�:
	seznam(const seznam& s) = delete;
	seznam& operator = (const seznam& s) = delete;
	*/
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
	// Vkl�d�n� do seznamu
	void vlo�_na_konec(const typ_hodnot &co){ u_seznam->vlo�_na_konec(co); }
	void vlo�_na_konec(typ_hodnot &&co) { u_seznam->vlo�_na_konec(std::move(co)); }
	void vlo�_na_za��tek(const typ_hodnot& co) { u_seznam->vlo�_na_za��tek(co); }
	void vlo�_na_za��tek(typ_hodnot&& co) { u_seznam->vlo�_na_za��tek(std::move(co)); }
	// Ostra�ov�n�
	void odstra�_prvn�() { u_seznam->odstra�_prvn�(); }
	void vypr�zdni() { u_seznam->vypr�zdni(); }
	// Pro lad�n�
	void vypi�() { u_seznam->vypi�(); }
	// Prohozen� obsahu dvou seznam�
	void proho�(seznam &s) { std::swap(u_seznam, s.u_seznam); }
	iter�tor_seznamu najdi(const T& co) const { return u_seznam->najdi(co); }
	iter�tor_seznamu begin() noexcept { return u_seznam->begin(); }
	konstantn�_iter�tor_seznamu begin() const noexcept {  return u_seznam->begin(); }
	konstantn�_iter�tor_seznamu cbegin() const noexcept { return u_seznam->cbegin(); }
	iter�tor_seznamu end() noexcept { return u_seznam->end(); }
	konstantn�_iter�tor_seznamu end() const noexcept { return u_seznam->end(); }
	konstantn�_iter�tor_seznamu cend() const noexcept { return u_seznam->cend(); }
};

template<class T, template<class T> class Alok�tor, class Implementace>
seznam<T, Alok�tor, Implementace>::seznam(std::initializer_list<T> seznam_inicializ�tor�)
{
	u_seznam = new seznam_impl<T, Alok�tor>(seznam_inicializ�tor�);
}


#endif //__SEZNAM_H__
