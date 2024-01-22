#include <vector>
#include <algorithm>
#include <iterator>

#include <iostream>
#include <ranges>

using namespace std;

auto sudost = [](int i) {return i % 2 == 0; };
auto ètverec = [](int i) {return i * i; };

vector<int> jen_sudá_na_druhou(vector<int>& numera)
{
	vector<int> sudá_numera;
	copy_if(begin(numera), end(numera), back_inserter(sudá_numera), sudost);
	vector<int> vısledek;
	transform(begin(sudá_numera), end(sudá_numera), back_inserter(vısledek), ètverec);
	return vısledek;
}

void vypiš(auto kontejner)
{
	cout << "(";
	for (auto i : kontejner)
	{
		cout << i << " ";
	}
	cout << ")" << endl;
}

auto jenSudáNáDruhou1(vector<int>& numera)
{
	return numera | std::views::filter(sudost) | std::views::transform(ètverec);
}

auto jenSudáNaDruhou2(vector<int>& data)
{
	return std::views::transform(std::views::filter(data, sudost), ètverec);
}

int main()
{
	vector<int> data{ 1,2,3,4,5,6,7,8 };
	
	vypiš(jen_sudá_na_druhou(data));
	vypiš(jenSudáNáDruhou1(data));
	auto x = jenSudáNáDruhou1(data);
	cout << typeid(x).name() << endl;
	vypiš(jenSudáNaDruhou2(data));
}

