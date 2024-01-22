#include <iostream>
#include <type_traits>
#include <stdlib.h>
using namespace std;

// Pou�it� oper�toru ��rka v n�vratov�m typu

template<class C,  class F>
auto test(C c, F f) -> decltype((c.*f)(), static_cast<void>(0))
{
	cout << "vol�na funkce s referenc�" << endl;
	(c.*f)();
}

template<class C, class F>
auto test(C c, F f) -> decltype((c->*f)(), static_cast<void>(0))
{
	cout << "vol�na funkce s ukazatelem" << endl;
	(c->*f)();
}

void test(...)
{
	cout << "Z�chytn� varianta" << endl;
}

struct X
{
	void f()
	{
		cout << "Vol�na metoda f" << endl;
	}
};

int main()
{
	system("CHCP 1250 > NUL");
	X x;
	cout << typeid(test(x, &X::f)).name() << endl;
	test(x, &X::f);
	test(&x, &X::f);
	test(42, 135);
}

