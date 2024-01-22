const int N = 18;

// Zobrazen� typu na typ
template<class T>
struct typ2typ
{
	using typ = T;
};

template<class T>
using typ2typ_t = typename typ2typ<T>::typ;


typ2typ<int>::typ a = 9;

// Zobrazen� hodnoty na typ
template<int N>
struct int2typ
{
	enum{v�sledek = N};
};

template<int N>
constexpr int int2typ_v = int2typ<N>::v�sledek;

template<bool podm�nka, class T, class U>
struct v�b�r_typu
{
	using typ = T;
};

template<class T, class U>
struct v�b�r_typu<false, T, U>
{
	using typ = U;
};

template<bool podm�nka, class T, class U>
using v�b�r_typu_t = typename v�b�r_typu<podm�nka, T, U>::typ;


// Alternativn� mo�nost
template<bool podm�nka, typename T, typename U>
struct v�b�r_typu_1;

template<typename T, typename U>
struct v�b�r_typu_1<true, T, U>
{
	using typ = T;
};

template<typename T, typename U>
struct v�b�r_typu_1<false, T, U>
{
	using typ = U;
};

template<bool podm�nka, typename T, typename U>
using v�b�r_typu_1_t = typename v�b�r_typu_1<podm�nka, T, U>::typ;

//typ2typ<int>::typ b = int2typ<5>::v�sledek;
typ2typ_t<int> b = int2typ_v<5>;

v�b�r_typu_t<(N < 10), int, long> c = 8;

// V�b�r ze t�� typ� ("switch")
template<int N, typename T1, typename T2, typename T3>
struct v�b�r_ze_3
{
	typedef T3 typ;
};

template<typename T1, typename T2, typename T3>
struct v�b�r_ze_3<0, T1, T2, T3>
{
	using typ = T1;
};

template<typename T1, typename T2, typename T3>
struct v�b�r_ze_3<1, T1, T2, T3>
{
	using typ = T2;
};

// V�po�et faktori�lu v dob� p�ekladu
template<int N>
struct faktori�l
{
	enum{v�sledek = N * faktori�l<N-1>::v�sledek};
};

template<>
struct faktori�l<0>
{
	enum{v�sledek = 1};
};

template<int N>
constexpr int faktori�l_v = faktori�l<N>::v�sledek;

// Generov�n� line�rn�ho k�du

// klasick� p��stup (bez metaprogramov�n�)

double skal_sou�in1(double *a, double *b, size_t N)
{
	double v�sledek = 0;
	for (int i = 0; i < N; i++)
		v�sledek += a[i] * b[i];
	return v�sledek;
}

double skal_sou�in2(double *a, double *b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

int main()
{
	int A[faktori�l_v<4>];
}