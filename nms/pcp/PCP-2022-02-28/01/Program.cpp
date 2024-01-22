// Lineární kód

template<int N>
struct skalární_souèin
{
	static inline double souèin(double *a, double* b)
	{
		return *a * *b + skalární_souèin<N - 1>::souèin(a + 1, b + 1);
	}
};

template<>
struct skalární_souèin<1>
{
	static inline double souèin(double *a, double *b)
	{
		return *a * *b;
	}
};


// Rùzné variantu faktoriálu

// Nelze použít static_assert
constexpr int faktoriál(int n)
{
	//static_assert(n >= 0, "chyba"); // nelze
	int výsledek = 1;
	while (n > 1) výsledek *= n--;
	return výsledek;
}

// Jak ho redy použít
template<int N>
struct výpoèet_faktoriálu
{
	static_assert(N >= 0, "nedovolená hodnota N");
	enum {výsledek = faktoriál(N) };
};

// Jiná možnost 
template<int N>
constexpr int faktoriál_f()
{
	static_assert(N >= 0, "Nedovolená hodnota N");
	int výsledek = 1, n = N;
	while (n > 1) výsledek *= n--;
	return výsledek;
}


int A[faktoriál(5)]{};

// Výpoèet mocniny v dobì pøekladu
template<int základ, unsigned exponent>
struct mocnina
{
	static const int polovina = mocnina<základ, exponent / 2>::výsledek;
	static const int výsledek = polovina * polovina*mocnina<základ, exponent % 2>::výsledek;
};

template<int základ>
struct mocnina<základ, 1>
{
	static_assert(základ != 0, "základ 0 není dovolen");
	static const int výsledek = základ;
};

template<int základ>
struct mocnina<základ, 0>
{
	static_assert(základ != 0, "základ 0 není dovolen");
	static const int výsledek = 1;
};


template<int základ, int exponent>
constexpr int mocnina_v = mocnina<základ, exponent>::výsledek;

// I záporný exponent

template<int základ, int exponent>
struct obecná_mocnina
{
	static const int exponentAbs = exponent < 0 ? -exponent : exponent;
	static const int polovina = obecná_mocnina<základ, exponentAbs / 2>::mezivýsledek;
	static const int mezivýsledek = polovina * polovina * obecná_mocnina<základ, exponentAbs % 2>::mezivýsledek;
	static constexpr double výsledek = exponent < 0 ? (1.0 / mezivýsledek) : mezivýsledek;
};

template<int základ>
struct obecná_mocnina<základ, 0>
{
	static const int mezivýsledek = 1;
	static constexpr double výsledek = 1.0;
	static_assert(základ != 0, "chyba");
};

template<int základ>
struct obecná_mocnina<základ, 1>
{
	static const int mezivýsledek = základ;
	static constexpr double výsledek = základ;
	static_assert(základ != 0, "chyba");
};


int main()
{
	int B[faktoriál_f<3>()]{};
	double a[3]{ 1,1,1, };
	double b[3]{ 1,2,3 };
	double x = skalární_souèin<3>::souèin(a, b);
	int n = mocnina<5, 3>::výsledek;
	int m = mocnina_v<2, 10>;
	double z = obecná_mocnina<2, -5>::výsledek;
}