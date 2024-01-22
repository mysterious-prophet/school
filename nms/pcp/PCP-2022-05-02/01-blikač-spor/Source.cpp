//Uk�zka sporu
//Blika�, skon�� pro nekonzistenci dat   RAII

#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <Windows.h>
#include <shared_mutex>
#include <limits.h>

using namespace std;

const int M = INT_MAX;

class blika�
{
private:
	int prvn� = 1, druh� = 0;
	int po��tadlo = 0;
	void kontrola() const
	{
		if (prvn� + druh� != 1)
		{
			string text = string("") + "Nekonzistence po " + to_string(po��tadlo) + " p�epnut�ch";
			MessageBoxA(0, text.data(), "Kon��me", MB_OK);
			cout << "Kon��me. " << text << endl;
			exit(1);
		}
	}
public:
	string text() const
	{
		char pom1[3], pom2[3];
		kontrola();   // Takhle to nejde!!! Aby m�la kontrola smysl, je t�eba 
		              // vytvo�it kopii, tu zkontrolovat, a je-li v po��dku, 
		              // pou��t k vytvo�en� v�sledku
		return string("") + to_string(prvn�) + " " + to_string(druh�);
	}

	void proho�()
	{
		druh� = prvn�;
		prvn� = 1 - druh�;
		po��tadlo++;
	}
};

blika� blikadlo;
bool hotovo = false;

mt19937 gener�tor;

void p�epni()
{
	for (int i = 1; i < M; i++)
	{
		blikadlo.proho�();
		this_thread::sleep_for(chrono::milliseconds(gener�tor() % 10));
	}
}


//p�ep�na� p�ep�nadlo;

class vypisova�
{
private:
	string minul� = "";
public:
	void vypi�()
	{
		while (!hotovo)
		{
			string text = blikadlo.text();
			if (text != minul�)
			{
				minul� = text;
				cout << text << endl;
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	}
	void operator()()
	{
		vypi�();
	}
};

int main()
{
	thread p�ep�naj�c�{ p�epni };
	//p�epni();
	//vypi�();
	thread vypisuj�c�{ vypisova�() };
	p�ep�naj�c�.join();
	vypisuj�c�.join();
	cout << "Dokon�eno jest." << endl;
}