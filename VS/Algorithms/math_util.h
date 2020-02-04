#include<iostream>
using namespace std;

template <typename T> 
class Element
{
public:
	Element(T val) 
	{
		internal = val;
	}
	T operator+(Element el)
	{
		return el.internal + this->internal;
	}
private:
	T internal;
};

void inner(int &a, int &b)
{
	cout << "#1" << endl;
}
void inner(int &&a, int &&b)
{
	cout << "#2" << endl ;
}

template <typename T1, typename T2> 
void outer(T1&& t1, T2&& t2)
{
	inner(std::forward<T1>(t1), std::forward<T2>(t2));
	//inner(t1, t2);
}
