#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

promise<string> pøíslib_výsledku;

class složitý_výpoèet
{
	mt19937 generátor;
public:
	void operator()()
	{
		cout << "provádíme složitý výpoèet\n";
		this_thread::sleep_for(milliseconds(generátor() % 1000 + 1000));
		odešli(pøíslib_výsledku);
	}
	void odešli(promise<string>& výsledek)
	{
		cout << "Odesílám výsledek" << endl;
		výsledek.set_value("Toto je výsledek");
	}
};

void dìlej_si_své()
{
	cout << "Dìlám své\n";
	this_thread::sleep_for(300ms);
}

složitý_výpoèet výpoèet;

template<class T>
bool hotovo(future<T> &budoucí_výsledek)
{
	return budoucí_výsledek.wait_for(0ms) == future_status::ready;
}

int main()
{
	jthread vlákno(výpoèet);
	future<string> výsledek_výpoètu = pøíslib_výsledku.get_future();
	while (!hotovo(výsledek_výpoètu))
	{
		dìlej_si_své();
	}
	cout << výsledek_výpoètu.get();

}