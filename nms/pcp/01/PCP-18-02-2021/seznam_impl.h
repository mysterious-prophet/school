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

	void vlo�_na_za��tek(T& data);
	void vlo�_na_za��tek(T&& data);
	void vlo�_na_konec(T&& data);
	void vlo�_na_konec(T& data);
	void odstra�_prvn�();
	void vypr�zdni();
	bool pr�zdn�() { return hlava == zar�ka; }
	
	
private:
	struct prvek;
	prvek *hlava, *zar�ka;
};

template<class T>
seznam_impl<T>::seznam_impl()
{
	hlava = zar�ka = new prvek(0, nullptr);
}

template<class T>
seznam_impl<T>::seznam_impl(initializer_list<T> data) 
	: seznam_impl()
{
	for (T hodnota : data)
	{
		vlo�_na_konec(hodnota);
	}

}

template<class T>
inline seznam_impl<T>::seznam_impl(seznam_impl<T>& vzor)
	:seznam_impl()
{
	for (prvek* pom = vzor.hlava; pom != vzor.zar�ka; pom = pom->dal��)
	{
		vlo�_na_konec(pom->data);
	}
}

template<class T>
inline seznam_impl<T>::seznam_impl(seznam_impl<T>&& vzor)
	:seznam_impl()
{
	swap(hlava, vzor.hlava);
	swap(zar�ka, vzor.zar�ka);
}

template<class T>
inline seznam_impl<T>::~seznam_impl()
{
	vypr�zdni();
	delete hlava;
}

template<class T>
inline seznam_impl<T> seznam_impl<T>::operator+(seznam_impl<T>& data)
{
	seznam_impl<T> v�sledek(*this);
	prvek *pom = data.hlava;
	while (pom != data.zar�ka)
	{
		v�sledek.vlo�_na_konec(pom->data);
		pom = pom->dal��;
	}
	return v�sledek;
}

template<class T>
inline void seznam_impl<T>::vlo�_na_za��tek(T & data)
{
	hlava = new prvek(data, hlava);
}

template<class T>
inline void seznam_impl<T>::vlo�_na_za��tek(T && data)
{
	hlava = new prvek(move(data), hlava);
}

template<class T>
inline void seznam_impl<T>::vlo�_na_konec(T && data)
{
	zar�ka->data = data;
	zar�ka->dal�� = new prvek(0, nullptr);
	zar�ka = zar�ka->dal��;
}

template<class T>
inline void seznam_impl<T>::vlo�_na_konec(T & data)
{
	zar�ka->data = data;
	zar�ka->dal�� = new prvek(0, nullptr);
	zar�ka = zar�ka->dal��;
}

template<class T>
inline void seznam_impl<T>::odstra�_prvn�()
{
	if (pr�zdn�())
	{
		return;
	}
	prvek *prvn� = hlava;
	hlava = hlava->dal��;
	delete prvn�;
}

template<class T>
inline void seznam_impl<T>::vypr�zdni()
{
	while (!pr�zdn�())
	{
		odstra�_prvn�();
	}
}

template<class T>
struct seznam_impl<T>::prvek
{
	T data;
	prvek* dal��;
	prvek(T&& data, prvek* dal��): data(move(data)), dal��(dal��) {}
	prvek(T& data, prvek* dal��) : data(data), dal��(dal��) {}
};

#endif // __SEZNAM_IMPL_H__
