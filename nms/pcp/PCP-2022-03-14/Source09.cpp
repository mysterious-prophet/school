#include <iostream>
using namespace std;

template<class T>
struct po��tadlo
{
	static size_t vytvo�eno;
	static size_t �ije;
	po��tadlo()
	{
		++vytvo�eno;
		++�ije;
	}
	po��tadlo(const po��tadlo&)
	{
		++vytvo�eno;
		++�ije;
	}
protected:
	~po��tadlo()
	{
		--�ije;
	}
};

template<typename T> size_t po��tadlo<T>::vytvo�eno{ 0 };
template<typename T> size_t po��tadlo<T>::�ije{ 0 };

class prvek : private po��tadlo<prvek>
{
	int data;
	prvek* dal��;
public:
	prvek(int data, prvek* dal��) : data(data), dal��(dal��) {}
	static size_t po�et_�iv�ch() { return �ije; }
	static size_t po�et_vytvo�en�ch() { return vytvo�eno; }
};

int main()
{
	prvek p1(9, 0);
	{
		prvek p2(8, 0);
		cout << "vytvo�eno:" << prvek::po�et_vytvo�en�ch() << endl;
		cout << "�ije:" << prvek::po�et_�iv�ch() << endl;
	}
	cout << "vytvo�eno:" << prvek::po�et_vytvo�en�ch() << endl;
	cout << "�ije:" << prvek::po�et_�iv�ch() << endl;
}