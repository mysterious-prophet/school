// Jedináèek

template<class T>
class Jedináèek
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
	Jedináèek() {};
private:
	Jedináèek(Jedináèek const&) = delete;
	Jedináèek(Jedináèek const&&) = delete;
	Jedináèek& operator = (Jedináèek const&) = delete;
	Jedináèek& operator = (Jedináèek const&&) = delete;
};

template<class T> T* Jedináèek<T>::p = nullptr;

class VzorovıJedináèek : public Jedináèek<VzorovıJedináèek>
{
	friend class Jedináèek<VzorovıJedináèek>;
	int a = 0;
public:
	int data()
	{
		return a;
	}
	void ulo(int data)
	{
		a = data;
	}
private :
	VzorovıJedináèek(){}
};

int main()
{
	VzorovıJedináèek& a1 = VzorovıJedináèek::instance();
}