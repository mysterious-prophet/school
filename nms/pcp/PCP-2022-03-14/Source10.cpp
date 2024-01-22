// Jedin��ek

template<class T>
class Jedin��ek
{
public:
	static T& instance()
	{
		if (p == nullptr)
		{
			p = new T;
		}
		return *p;
	}
protected:
	static T* p;
	Jedin��ek() {};
private:
	Jedin��ek(Jedin��ek const&) = delete;
	Jedin��ek(Jedin��ek const&&) = delete;
	Jedin��ek& operator = (Jedin��ek const&) = delete;
	Jedin��ek& operator = (Jedin��ek const&&) = delete;
};

template<class T> T* Jedin��ek<T>::p = nullptr;

class Vzorov�Jedin��ek : public Jedin��ek<Vzorov�Jedin��ek>
{
	friend class Jedin��ek<Vzorov�Jedin��ek>;
	int a = 0;
public:
	int data()
	{
		return a;
	}
	void ulo�(int data)
	{
		a = data;
	}
private :
	Vzorov�Jedin��ek(){}
};

int main()
{
	Vzorov�Jedin��ek& a1 = Vzorov�Jedin��ek::instance();
}