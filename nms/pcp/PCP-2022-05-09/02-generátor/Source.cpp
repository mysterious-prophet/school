#include <iostream>
#include <coroutine>

using namespace std;

template<class T>
struct generátor
{
	struct promise_type;
	using handle = coroutine_handle<promise_type>;
	bool další();
	T hodnota();
	generátor(generátor const&) = delete;
	generátor(generátor&& param) noexcept : korutina(param.korutina)
	{
		param.korutina = nullptr;
	}
	~generátor() { if (korutina)korutina.destroy(); }
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
	void return_void(){ }
	auto yield_value(T hodnota);
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

// ----------------

generátor<int> f(int n)
{
	int i = 0;
	while (++i <= n)
	{
		co_yield i;
	}
}

int main()
{
	auto posloupnost = f(5);
	while (posloupnost.další())
	{
		cout << posloupnost.hodnota() << ' ';
	}
	cout << endl;
}