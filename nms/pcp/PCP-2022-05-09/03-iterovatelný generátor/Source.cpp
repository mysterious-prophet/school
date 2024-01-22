#include <iostream>
#include <coroutine>

using namespace std;

template<class T>
struct generátor
{
	struct promise_type;
	using handle = coroutine_handle<promise_type>;
	class iterátor;
	bool další();
	T hodnota();
	generátor(generátor const&) = delete;
	generátor(generátor&& param) noexcept : korutina(param.korutina)
	{
		param.korutina = nullptr;
	}
	~generátor() { if (korutina)korutina.destroy(); }
	iterátor begin();
	default_sentinel_t end() { return default_sentinel; }
private:
	handle korutina;
	generátor(handle h) : korutina(h) {}
};

template<class T>
struct generátor<T>::promise_type
{
	T aktuální_hodnota_výsledku;
	static auto get_return_type_on_allocation_failure();
	auto get_return_object();
	auto initial_suspend();
	auto final_suspend() noexcept;
	void unhandled_exception();
	void return_void() { }
	auto yield_value(T hodnota);
};

template<class T>
class generátor<T>::iterátor
{
public:
	void operator++()
	{
		korutina.resume();
	}
	const T& operator*() const
	{
		return korutina.promise().aktuální_hodnota_výsledku;
	}
	bool operator==(default_sentinel_t) const
	{
		return !korutina || korutina.done();
	}

	explicit iterátor(const handle korutina): korutina(korutina){}
private:
	handle korutina;
};

// Metody generátoru
template<class T>
bool generátor<T>::další()
{
	return korutina ? (korutina.resume(), !korutina.done()) : false;
}

template<class T>
T generátor<T>::hodnota()
{
	return korutina.promise().aktuální_hodnota_výsledku;
}

// Metody promise_type

template<class T>
auto generátor<T>::promise_type::get_return_type_on_allocation_failure()
{
	return generátor(nullptr);
}

template<class T>
auto generátor<T>::promise_type::get_return_object()
{
	return generátor{ handle::from_promise(*this) };
}

template<class T>
auto generátor<T>::promise_type::initial_suspend()
{
	return suspend_always{};
}

template<class T>
auto generátor<T>::promise_type::final_suspend() noexcept
{
	return suspend_always{};
}

template<class T>
void generátor<T>::promise_type::unhandled_exception()
{
	terminate();
}

template<class T>
auto generátor<T>::promise_type::yield_value(T hodnota)
{
	aktuální_hodnota_výsledku = hodnota;
	return suspend_always{};
}

// metody iterátoru
template<class T>
generátor<T>::iterátor generátor<T>::begin()
{
	if (korutina)
	{
		korutina.resume();
	}
	return iterátor{ korutina };
}

// ----------------

generátor<int> f(int n)
{
	int i = 0;
	while (++i <= n)
	{
		co_yield i;
	}
}

template<class T>
generátor<int> úsek(T první, const T poslední)
{
	while (první < poslední)
	{
		co_yield první++;
	}
}

int main()
{
	for (const char i : úsek(char(65), char(91)))
	{
		cout << i << ' ';
	}
	cout << endl;
}