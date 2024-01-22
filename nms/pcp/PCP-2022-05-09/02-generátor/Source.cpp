#include <iostream>
#include <coroutine>

using namespace std;

template<class T>
struct gener�tor
{
	struct promise_type;
	using handle = coroutine_handle<promise_type>;
	bool dal��();
	T hodnota();
	gener�tor(gener�tor const&) = delete;
	gener�tor(gener�tor&& param) noexcept : korutina(param.korutina)
	{
		param.korutina = nullptr;
	}
	~gener�tor() { if (korutina)korutina.destroy(); }
private:
	handle korutina;
	gener�tor(handle h) : korutina(h) {}
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
	void return_void(){ }
	auto yield_value(T hodnota);
};

// Metody gener�toru
template<class T>
bool gener�tor<T>::dal��()
{
	return korutina ? (korutina.resume(), !korutina.done()) : false;
}

template<class T> 
T gener�tor<T>::hodnota()
{
	return korutina.promise().aktu�ln�_hodnota_v�sledku;
}



// Metody promise_type

template<class T>
auto gener�tor<T>::promise_type::get_return_type_on_allocation_failure()
{
	return gener�tor(nullptr);
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

// ----------------

gener�tor<int> f(int n)
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
	while (posloupnost.dal��())
	{
		cout << posloupnost.hodnota() << ' ';
	}
	cout << endl;
}