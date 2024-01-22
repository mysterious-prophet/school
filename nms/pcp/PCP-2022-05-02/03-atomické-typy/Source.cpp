//Ukázka sporu
//Blikaè, skonèí pro nekonzistenci dat   RAII

#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <Windows.h>
#include <shared_mutex>
#include <limits.h>
#include <atomic>
#include <stdio.h>

using namespace std;

const int M = INT_MAX;
atomic_bool hotovo = false;

class blikaè
{
private:
	int první = 1, druhý = 0;
	int poèítadlo = 0;
	void kontrola() const
	{
		if (první + druhý != 1)
		{
			string text = string("") + "Nekonzistence po " + to_string(poèítadlo) + " pøepnutích";
			MessageBoxA(0, text.data(), "Konèíme", MB_OK);
			cout << "Konèíme. " << text << endl;
			exit(1);
		}
	}
public:
	string text() const
	{
		char pom1[3], pom2[3];
		kontrola();   // Takhle to nejde!!! Aby mìla kontrola smysl, je tøeba 
					  // vytvoøit kopii, tu zkontrolovat, a je-li v poøádku, 
					  // použít k vytvoøení výsledku
		return string("") + to_string(první) + " " + to_string(druhý);
	}

	void prohoï()
	{
		druhý = první;
		první = 1 - druhý;
		poèítadlo++;
	}
};

blikaè blikadlo;


mt19937 generátor;

void pøepni()
{
	for (int i = 1; i < M; i++)
	{
		if (hotovo)break;
		blikadlo.prohoï();
		this_thread::sleep_for(chrono::milliseconds(generátor() % 10));
	}
}


//pøepínaè pøepínadlo;

class vypisovaè
{
private:
	string minulé = "";
public:
	void vypiš()
	{
		while (!hotovo)
		{
			if (hotovo)break;
			string text = blikadlo.text();
			if (text != minulé)
			{
				minulé = text;
				cout << text << endl;
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	}
	void operator()()
	{
		vypiš();
	}
};

void pøerušovaè()
{
	getchar();
	hotovo = true;
}

int main()
{
	jthread pøepínající{ pøepni };
	jthread vypisující{ vypisovaè() };
	jthread pøerušující{ pøerušovaè };
	//pøepínající.join();
	//vypisující.join();
	//pøerušující.join();
	cout << "Dokonèeno jest." << endl;
}