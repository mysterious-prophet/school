#include <iostream>
#include <type_traits>

using namespace std;

template<int N>
enable_if_t<(N % 2 == 0)>
test()
{
	cout << "Parametr je sudý" << endl;
}

template<int N>
enable_if_t<(N % 2 == 1)>
test()
{
	cout << "parametr je lichý" << endl;
}

int main()
{
	test<5>();
}