#include <iostream>
#include <type_traits>

using namespace std;

template<int N>
enable_if_t<(N % 2 == 0)>
test()
{
	cout << "Parametr je sud�" << endl;
}

template<int N>
enable_if_t<(N % 2 == 1)>
test()
{
	cout << "parametr je lich�" << endl;
}

int main()
{
	test<5>();
}