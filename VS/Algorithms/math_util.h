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

