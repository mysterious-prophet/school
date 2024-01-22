#include <ranges>
#include<iostream>

int a[]{ 1,2,3,4,5,6,7,8,9,10 };
auto seznam_inic = { 1,2,3,4,5 };

void vypi�(auto rozsah)
{
	std::cout << "(";
	for (auto i : rozsah)
	{
		std::cout << i << " ";
	}
	std::cout << ")" << std::endl;
}


int main()
{
	vypi�(std::views::counted(a, 3));
	vypi�(std::views::counted(seznam_inic.begin() + 1, 3));
}

