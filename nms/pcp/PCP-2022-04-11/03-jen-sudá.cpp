#include <vector>
#include <algorithm>
#include <iterator>

#include <iostream>
#include <ranges>

using namespace std;

auto sudost = [](int i) {return i % 2 == 0; };
auto �tverec = [](int i) {return i * i; };

vector<int> jen_sud�_na_druhou(vector<int>& numera)
{
	vector<int> sud�_numera;
	copy_if(begin(numera), end(numera), back_inserter(sud�_numera), sudost);
	vector<int> v�sledek;
	transform(begin(sud�_numera), end(sud�_numera), back_inserter(v�sledek), �tverec);
	return v�sledek;
}

void vypi�(auto kontejner)
{
	cout << "(";
	for (auto i : kontejner)
	{
		cout << i << " ";
	}
	cout << ")" << endl;
}

auto jenSud�N�Druhou1(vector<int>& numera)
{
	return numera | std::views::filter(sudost) | std::views::transform(�tverec);
}

auto jenSud�NaDruhou2(vector<int>& data)
{
	return std::views::transform(std::views::filter(data, sudost), �tverec);
}

int main()
{
	vector<int> data{ 1,2,3,4,5,6,7,8 };
	
	vypi�(jen_sud�_na_druhou(data));
	vypi�(jenSud�N�Druhou1(data));
	auto x = jenSud�N�Druhou1(data);
	cout << typeid(x).name() << endl;
	vypi�(jenSud�NaDruhou2(data));
}

