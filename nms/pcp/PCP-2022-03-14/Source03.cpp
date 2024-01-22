// SFINAE
// Použití SFINAE pro volbu jedné z funkcí (podle parity parametru šablony)

#include <iostream>
#include <stdlib.h>



template<int N>
void test(char(*)[N % 2 == 0] = 0)
{
	std::cout << "Parametr " << N << " je sudý " << std::endl;
}

template<int N>
void test(char(*)[N % 2 == 1] = 0)
{
	std::cout << "Parametr " << N << " je lichý " << std::endl;
}

int main()
{
	system("CHCP 1250 > NUL");
	test<3>();
	test<4>();
}