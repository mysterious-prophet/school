// Line�rn� k�d

template<int N>
struct skal�rn�_sou�in
{
	static inline double sou�in(double *a, double* b)
	{
		return *a * *b + skal�rn�_sou�in<N - 1>::sou�in(a + 1, b + 1);
	}
};

template<>
struct skal�rn�_sou�in<1>
{
	static inline double sou�in(double *a, double *b)
	{
		return *a * *b;
	}
};


// R�zn� variantu faktori�lu

// Nelze pou��t static_assert
constexpr int faktori�l(int n)
{
	//static_assert(n >= 0, "chyba"); // nelze
	int v�sledek = 1;
	while (n > 1) v�sledek *= n--;
	return v�sledek;
}

// Jak ho redy pou��t
template<int N>
struct v�po�et_faktori�lu
{
	static_assert(N >= 0, "nedovolen� hodnota N");
	enum {v�sledek = faktori�l(N) };
};

// Jin� mo�nost 
template<int N>
constexpr int faktori�l_f()
{
	static_assert(N >= 0, "Nedovolen� hodnota N");
	int v�sledek = 1, n = N;
	while (n > 1) v�sledek *= n--;
	return v�sledek;
}


int A[faktori�l(5)]{};

// V�po�et mocniny v dob� p�ekladu
template<int z�klad, unsigned exponent>
struct mocnina
{
	static const int polovina = mocnina<z�klad, exponent / 2>::v�sledek;
	static const int v�sledek = polovina * polovina*mocnina<z�klad, exponent % 2>::v�sledek;
};

template<int z�klad>
struct mocnina<z�klad, 1>
{
	static_assert(z�klad != 0, "z�klad 0 nen� dovolen");
	static const int v�sledek = z�klad;
};

template<int z�klad>
struct mocnina<z�klad, 0>
{
	static_assert(z�klad != 0, "z�klad 0 nen� dovolen");
	static const int v�sledek = 1;
};


template<int z�klad, int exponent>
constexpr int mocnina_v = mocnina<z�klad, exponent>::v�sledek;

// I z�porn� exponent

template<int z�klad, int exponent>
struct obecn�_mocnina
{
	static const int exponentAbs = exponent < 0 ? -exponent : exponent;
	static const int polovina = obecn�_mocnina<z�klad, exponentAbs / 2>::meziv�sledek;
	static const int meziv�sledek = polovina * polovina * obecn�_mocnina<z�klad, exponentAbs % 2>::meziv�sledek;
	static constexpr double v�sledek = exponent < 0 ? (1.0 / meziv�sledek) : meziv�sledek;
};

template<int z�klad>
struct obecn�_mocnina<z�klad, 0>
{
	static const int meziv�sledek = 1;
	static constexpr double v�sledek = 1.0;
	static_assert(z�klad != 0, "chyba");
};

template<int z�klad>
struct obecn�_mocnina<z�klad, 1>
{
	static const int meziv�sledek = z�klad;
	static constexpr double v�sledek = z�klad;
	static_assert(z�klad != 0, "chyba");
};


int main()
{
	int B[faktori�l_f<3>()]{};
	double a[3]{ 1,1,1, };
	double b[3]{ 1,2,3 };
	double x = skal�rn�_sou�in<3>::sou�in(a, b);
	int n = mocnina<5, 3>::v�sledek;
	int m = mocnina_v<2, 10>;
	double z = obecn�_mocnina<2, -5>::v�sledek;
}