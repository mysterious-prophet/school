#include <iostream>
#include <coroutine>
#include <ranges>
#include <concepts>
#include <iterator>
#include <vector>
#include <limits>

using namespace std;

template<class T>
struct gener�tor
{
	struct promise_type;
	using handle = std::coroutine_handle<promise_type>;
	class iter�tor;
	bool dal��();
	T hodnota();
	//gener�tor(gener�tor const& param) : korutina(param.korutina) {};
	gener�tor(gener�tor const&) = delete;
	gener�tor(gener�tor&& param) noexcept : korutina(param.korutina) { param.korutina = nullptr; }
	gener�tor() : korutina(nullptr) {}
	~gener�tor() { if (korutina) korutina.destroy(); }
	iter�tor begin();
	std::default_sentinel_t end();
	/*gener�tor& operator==(gener�tor param)
	{
		korutina = param.korutina;
		return *this;
	}*/

private:
	gener�tor(handle h) : korutina(h) {}
	handle korutina;
};

template<class T>
struct gener�tor<T>::promise_type
{
	T aktu�ln�_hodnota_v�sledku;
	static auto get_return_type_on_allocation_failure();
	auto get_return_object();
	auto initial_suspend();
	auto final_suspend() noexcept;
	void unhandled_exception();
	void return_void() {  };
	auto yield_value(T hodnota);
};

template<class T>
class gener�tor<T>::iter�tor
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using reference = T&;
	using pointer = T*;

	iter�tor& operator++() {
		korutina.resume();
		return *this;
	}
	void operator++(int)
	{
		korutina.resume();
	}

	const T& operator*() const {
		return korutina.promise().aktu�ln�_hodnota_v�sledku;
	}
	bool operator==(std::default_sentinel_t) const {
		return !korutina || korutina.done();
	}

	explicit iter�tor(const handle korutina) :
		korutina{ korutina }
	{}
	iter�tor() : korutina(nullptr) {}

private:
	handle korutina;
};

// Metody gener�toru
template<class T>
T gener�tor<T>::hodnota()
{
	return korutina.promise().aktu�ln�_hodnota_v�sledku;
}

template<class T>
bool gener�tor<T>::dal��()
{
	return korutina ? (korutina.resume(), !korutina.done()) : false;
}

template<class T>
typename gener�tor<T>::iter�tor gener�tor<T>::begin()
{
	if (korutina)
	{
		korutina.resume();
	}
	return iter�tor{ korutina };
}

template<class T>
std::default_sentinel_t gener�tor<T>::end()
{
	return {};
}


// Metody p��slibu
template<class T>
auto gener�tor<T>::promise_type::get_return_type_on_allocation_failure()
{
	return gener�tor{ nullptr };
}

template<class T>
auto gener�tor<T>::promise_type::get_return_object()
{
	return gener�tor{ handle::from_promise(*this) };
}

template<class T>
auto gener�tor<T>::promise_type::initial_suspend()
{
	return suspend_always{};
}

template<class T>
auto gener�tor<T>::promise_type::final_suspend() noexcept
{
	return suspend_always{};
}

template<class T>
void gener�tor<T>::promise_type::unhandled_exception()
{
	terminate();
}

template<class T>
auto gener�tor<T>::promise_type::yield_value(T hodnota)
{
	aktu�ln�_hodnota_v�sledku = hodnota;
	return suspend_always{};
}

// --------- 

gener�tor<int> f(int n)
{
	int i = 0;
	while (++i < n)
	{
		co_yield i;
	}
}


template<class T>
gener�tor<T> �sek(T prvn�, const T posledn�, const T krok)
{
	while (prvn� < posledn�)
	{
		co_yield prvn�;
		prvn� += krok;
	}
}

class iota_t
{
public:
	template<integral T>
	gener�tor<T>& operator()(T prvn�, T posledn� = numeric_limits<T>::max(), T krok = 1)
	{
		static vector<gener�tor<T>> data{};
		data.push_back(�sek(prvn�, posledn�, krok));
		return data.back();
	}
};

iota_t iota;

void v�pis(const auto& rozsah)
{
	for (auto i : rozsah)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
}


int main()
{
	v�pis(iota(1, 3, 1) | ranges::views::transform([](int c) {return c * c; }));
	v�pis(iota(1, 4, 1) | ranges::views::transform([](int c) {return c * c; }));
	auto z = iota(1L, 4L, 1L) | ranges::views::transform([](int c) {return c * c; });
	auto u = iota('A', 'F', char(1)) | ranges::views::transform([](auto c) {return char(c - 'A' + 'a'); });
	auto v = iota(1) | ranges::views::take(10);
	v�pis(z);
	v�pis(u);
	v�pis(v);
}