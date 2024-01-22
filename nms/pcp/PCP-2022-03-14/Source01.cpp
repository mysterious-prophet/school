// Klasické použití SFINAE

#include <iostream>
#include <stdlib.h>

using namespace std;

template<class T>
class X
{
public:
	using typ = T;
};

template<class T>
int f(typename  T::typ* param = nullptr)
{
	return sizeof(*param);
}

template<class T>
int f(T param)
{
	return sizeof(T);
}

int main()
{
	cout << f<int>(0) << endl;
	X<long long>::typ p = 0;
	cout << f<X<long long>>(&p) << endl;
}