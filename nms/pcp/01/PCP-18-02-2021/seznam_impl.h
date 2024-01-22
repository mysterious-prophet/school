#ifndef __SEZNAM_IMPL_H__
#define __SEZNAM_IMPL_H__

#include <initializer_list>
#include <utility>
#include <algorithm>

using namespace std;

template<class T>
class seznam_impl
{
public:
	
	seznam_impl();
	seznam_impl(initializer_list<T> data);
	seznam_impl(seznam_impl<T>& vzor);
	seznam_impl(seznam_impl<T>&& vzor);
	~seznam_impl();
	seznam_impl<T> operator+(seznam_impl<T>& data);

	void vlož_na_zaèátek(T& data);
	void vlož_na_zaèátek(T&& data);
	void vlož_na_konec(T&& data);
	void vlož_na_konec(T& data);
	void odstraò_první();
	void vyprázdni();
	bool prázdný() { return hlava == zarážka; }
	
	
private:
	struct prvek;
	prvek *hlava, *zarážka;
};

template<class T>
seznam_impl<T>::seznam_impl()
{
	hlava = zarážka = new prvek(0, nullptr);
}

template<class T>
seznam_impl<T>::seznam_impl(initializer_list<T> data) 
	: seznam_impl()
{
	for (T hodnota : data)
	{
		vlož_na_konec(hodnota);
	}

}

template<class T>
inline seznam_impl<T>::seznam_impl(seznam_impl<T>& vzor)
	:seznam_impl()
{
	for (prvek* pom = vzor.hlava; pom != vzor.zarážka; pom = pom->další)
	{
		vlož_na_konec(pom->data);
	}
}

template<class T>
inline seznam_impl<T>::seznam_impl(seznam_impl<T>&& vzor)
	:seznam_impl()
{
	swap(hlava, vzor.hlava);
	swap(zarážka, vzor.zarážka);
}

template<class T>
inline seznam_impl<T>::~seznam_impl()
{
	vyprázdni();
	delete hlava;
}

template<class T>
inline seznam_impl<T> seznam_impl<T>::operator+(seznam_impl<T>& data)
{
	seznam_impl<T> výsledek(*this);
	prvek *pom = data.hlava;
	while (pom != data.zarážka)
	{
		výsledek.vlož_na_konec(pom->data);
		pom = pom->další;
	}
	return výsledek;
}

template<class T>
inline void seznam_impl<T>::vlož_na_zaèátek(T & data)
{
	hlava = new prvek(data, hlava);
}

template<class T>
inline void seznam_impl<T>::vlož_na_zaèátek(T && data)
{
	hlava = new prvek(move(data), hlava);
}

template<class T>
inline void seznam_impl<T>::vlož_na_konec(T && data)
{
	zarážka->data = data;
	zarážka->další = new prvek(0, nullptr);
	zarážka = zarážka->další;
}

template<class T>
inline void seznam_impl<T>::vlož_na_konec(T & data)
{
	zarážka->data = data;
	zarážka->další = new prvek(0, nullptr);
	zarážka = zarážka->další;
}

template<class T>
inline void seznam_impl<T>::odstraò_první()
{
	if (prázdný())
	{
		return;
	}
	prvek *první = hlava;
	hlava = hlava->další;
	delete první;
}

template<class T>
inline void seznam_impl<T>::vyprázdni()
{
	while (!prázdný())
	{
		odstraò_první();
	}
}

template<class T>
struct seznam_impl<T>::prvek
{
	T data;
	prvek* další;
	prvek(T&& data, prvek* další): data(move(data)), další(další) {}
	prvek(T& data, prvek* další) : data(data), další(další) {}
};

#endif // __SEZNAM_IMPL_H__
