export module A;
import <iostream>;

inline void f_m�stn�();

static void f_statick�();

export struct X;

//export void f_chyba(); // nem�lo by proj�t

void zpracuj_x(X* x)
{
	f_statick�();
	f_m�stn�();
	f_chyba();
}

export X* tov�rna();

module : private;

struct X{};
struct X* tov�rna()
{
	return new X;
}

void f_chyba() 
{
	std::cout << "f_chyba" << std::endl;
}

void f_m�stn�()
{
	std::cout << "f_m�stn�" << std::endl;
}

void f_statick�()
{
	std::cout << "f_statick�" << std::endl;
}