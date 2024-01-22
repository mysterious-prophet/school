const int N = 18;

// Zobrazení typu na typ
template<class T>
struct typ2typ
{
	using typ = T;
};

template<class T>
using typ2typ_t = typename typ2typ<T>::typ;


typ2typ<int>::typ a = 9;

// Zobrazení hodnoty na typ
template<int N>
struct int2typ
{
	enum{výsledek = N};
};

template<int N>
constexpr int int2typ_v = int2typ<N>::výsledek;

template<bool podmínka, class T, class U>
struct výbìr_typu
{
	using typ = T;
};

template<class T, class U>
struct výbìr_typu<false, T, U>
{
	using typ = U;
};

template<bool podmínka, class T, class U>
using výbìr_typu_t = typename výbìr_typu<podmínka, T, U>::typ;


// Alternativní možnost
template<bool podmínka, typename T, typename U>
struct výbìr_typu_1;

template<typename T, typename U>
struct výbìr_typu_1<true, T, U>
{
	using typ = T;
};

template<typename T, typename U>
struct výbìr_typu_1<false, T, U>
{
	using typ = U;
};

template<bool podmínka, typename T, typename U>
using výbìr_typu_1_t = typename výbìr_typu_1<podmínka, T, U>::typ;

//typ2typ<int>::typ b = int2typ<5>::výsledek;
typ2typ_t<int> b = int2typ_v<5>;

výbìr_typu_t<(N < 10), int, long> c = 8;

// Výbìr ze tøí typù ("switch")
template<int N, typename T1, typename T2, typename T3>
struct výbìr_ze_3
{
	typedef T3 typ;
};

template<typename T1, typename T2, typename T3>
struct výbìr_ze_3<0, T1, T2, T3>
{
	using typ = T1;
};

template<typename T1, typename T2, typename T3>
struct výbìr_ze_3<1, T1, T2, T3>
{
	using typ = T2;
};

// Výpoèet faktoriálu v dobì pøekladu
template<int N>
struct faktoriál
{
	enum{výsledek = N * faktoriál<N-1>::výsledek};
};

template<>
struct faktoriál<0>
{
	enum{výsledek = 1};
};

template<int N>
constexpr int faktoriál_v = faktoriál<N>::výsledek;

// Generování lineárního kódu

// klasický pøístup (bez metaprogramování)

double skal_souèin1(double *a, double *b, size_t N)
{
	double výsledek = 0;
	for (int i = 0; i < N; i++)
		výsledek += a[i] * b[i];
	return výsledek;
}

double skal_souèin2(double *a, double *b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

int main()
{
	int A[faktoriál_v<4>];
}