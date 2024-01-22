// Odvozen� bal�ku parametr�: v�po�et faktori�lu v dob� p�ekladu
#include <iostream>
#include <type_traits>

using namespace std;

template<size_t ... data>
constexpr size_t sou�in(std::index_sequence<data...>)
{
	return ((data + 1) * ...);
}

template<size_t N>
constexpr size_t faktori�l()
{
	return sou�in(make_index_sequence<N>{});
}

int main()
{
	auto y = sou�in(index_sequence<2, 2, 2>{});
	cout << y << endl;
	int A[faktori�l<3>()];
}