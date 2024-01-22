#include <iostream>
using namespace std;

template<class T>
struct poèítadlo
{
	static size_t vytvoøeno;
	static size_t žije;
	poèítadlo()
	{
		++vytvoøeno;
		++žije;
	}
	poèítadlo(const poèítadlo&)
	{
		++vytvoøeno;
		++žije;
	}
protected:
	~poèítadlo()
	{
		--žije;
	}
};

template<typename T> size_t poèítadlo<T>::vytvoøeno{ 0 };
template<typename T> size_t poèítadlo<T>::žije{ 0 };

class prvek : private poèítadlo<prvek>
{
	int data;
	prvek* další;
public:
	prvek(int data, prvek* další) : data(data), další(další) {}
	static size_t poèet_živých() { return žije; }
	static size_t poèet_vytvoøených() { return vytvoøeno; }
};

int main()
{
	prvek p1(9, 0);
	{
		prvek p2(8, 0);
		cout << "vytvoøeno:" << prvek::poèet_vytvoøených() << endl;
		cout << "žije:" << prvek::poèet_živých() << endl;
	}
	cout << "vytvoøeno:" << prvek::poèet_vytvoøených() << endl;
	cout << "žije:" << prvek::poèet_živých() << endl;
}