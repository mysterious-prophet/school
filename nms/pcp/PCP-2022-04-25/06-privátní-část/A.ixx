export module A;
import <iostream>;

inline void f_místní();

static void f_statická();

export struct X;

//export void f_chyba(); // nemìlo by projít

void zpracuj_x(X* x)
{
	f_statická();
	f_místní();
	f_chyba();
}

export X* továrna();

module : private;

struct X{};
struct X* továrna()
{
	return new X;
}

void f_chyba() 
{
	std::cout << "f_chyba" << std::endl;
}

void f_místní()
{
	std::cout << "f_místní" << std::endl;
}

void f_statická()
{
	std::cout << "f_statická" << std::endl;
}