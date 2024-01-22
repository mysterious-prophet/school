#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

promise<string> p��slib_v�sledku;

class slo�it�_v�po�et
{
	mt19937 gener�tor;
public:
	void operator()()
	{
		cout << "prov�d�me slo�it� v�po�et\n";
		this_thread::sleep_for(milliseconds(gener�tor() % 1000 + 1000));
		ode�li(p��slib_v�sledku);
	}
	void ode�li(promise<string>& v�sledek)
	{
		cout << "Odes�l�m v�sledek" << endl;
		v�sledek.set_value("Toto je v�sledek");
	}
};

void d�lej_si_sv�()
{
	cout << "D�l�m sv�\n";
	this_thread::sleep_for(300ms);
}

slo�it�_v�po�et v�po�et;

template<class T>
bool hotovo(future<T> &budouc�_v�sledek)
{
	return budouc�_v�sledek.wait_for(0ms) == future_status::ready;
}

int main()
{
	jthread vl�kno(v�po�et);
	future<string> v�sledek_v�po�tu = p��slib_v�sledku.get_future();
	while (!hotovo(v�sledek_v�po�tu))
	{
		d�lej_si_sv�();
	}
	cout << v�sledek_v�po�tu.get();

}