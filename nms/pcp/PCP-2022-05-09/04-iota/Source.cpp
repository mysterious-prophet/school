#include <iostream>
#include <coroutine>
#include <ranges>
#include <concepts>
#include <iterator>
#include <vector>
#include <limits>

using namespace std;

template<class T>
struct generátor
{
	struct promise_type;
	using handle = std::coroutine_handle<promise_type>;
	class iterátor;
	bool další();
	T hodnota();
	//generátor(generátor const& param) : korutina(param.korutina) {};
	generátor(generátor const&) = delete;
	generátor(generátor&& param) noexcept : korutina(param.korutina) { param.korutina = nullptr; }
	generátor() : korutina(nullptr) {}
	~generátor() { if (korutina) korutina.destroy(); }
	iterátor begin();
	std::default_sentinel_t end();
	/*generátor& operator==(generátor param)
	{
		korutina = param.korutina;
		return *this;
	}*/

private:
	generátor(handle h) : korutina(h) {}
	handle korutina;
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
	void return_void() {  };
	auto yield_value(T hodnota);
};

template<class T>
class generátor<T>::iterátor
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using reference = T&;
	using pointer = T*;

	iterátor& operator++() {
		korutina.resume();
		return *this;
	}
	void operator++(int)
	{
		korutina.resume();
	}

	const T& operator*() const {
		return korutina.promise().aktuální_hodnota_výsledku;
	}
	bool operator==(std::default_sentinel_t) const {
		return !korutina || korutina.done();
	}

	explicit iterátor(const handle korutina) :
		korutina{ korutina }
	{}
	iterátor() : korutina(nullptr) {}

private:
	handle korutina;
};

// Metody generátoru
template<class T>
T generátor<T>::hodnota()
{
	return korutina.promise().aktuální_hodnota_výsledku;
}

template<class T>
bool generátor<T>::další()
{
	return korutina ? (korutina.resume(), !korutina.done()) : false;
}

template<class T>
typename generátor<T>::iterátor generátor<T>::begin()
{
	if (korutina)
	{
		korutina.resume();
	}
	return iterátor{ korutina };
}

template<class T>
std::default_sentinel_t generátor<T>::end()
{
	return {};
}


// Metody pøíslibu
template<class T>
auto generátor<T>::promise_type::get_return_type_on_allocation_failure()
{
	return generátor{ nullptr };
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

// --------- 

generátor<int> f(int n)
{
	int i = 0;
	while (++i < n)
	{
		co_yield i;
	}
}


template<class T>
generátor<T> úsek(T první, const T poslední, const T krok)
{
	while (první < poslední)
	{
		co_yield první;
		první += krok;
	}
}

class iota_t
{
public:
	template<integral T>
	generátor<T>& operator()(T první, T poslední = numeric_limits<T>::max(), T krok = 1)
	{
		static vector<generátor<T>> data{};
		data.push_back(úsek(první, poslední, krok));
		return data.back();
	}
};

iota_t iota;

void výpis(const auto& rozsah)
{
	for (auto i : rozsah)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
}


int main()
{
	výpis(iota(1, 3, 1) | ranges::views::transform([](int c) {return c * c; }));
	výpis(iota(1, 4, 1) | ranges::views::transform([](int c) {return c * c; }));
	auto z = iota(1L, 4L, 1L) | ranges::views::transform([](int c) {return c * c; });
	auto u = iota('A', 'F', char(1)) | ranges::views::transform([](auto c) {return char(c - 'A' + 'a'); });
	auto v = iota(1) | ranges::views::take(10);
	výpis(z);
	výpis(u);
	výpis(v);
}