#include<iostream>
#include "testcases.h"

using namespace std;

class Heap1 {
public:
	// Constructor
	Heap1() {
		m_data = 0;
		cout << "default-ctor" << endl;
	}

	Heap1(int data) {
		m_data = data;
		cout << "ctor" << endl;
	}

	Heap1(const Heap1& rhs)
	{
		this->m_data = rhs.m_data;
		cout << "copy-ctor" << endl;
	};
	Heap1(const Heap1&& rhs)
	{
		this->m_data = rhs.m_data;
		cout << "copy-move-ctor" << endl;
	};
	Heap1& operator=(const Heap1& rhs)
	{
		this->m_data = rhs.m_data;
		cout << "assign-ctor" << endl;
		return *this;
	};
	Heap1& operator=(const Heap1&& rhs)
	{
		this->m_data = rhs.m_data;
		cout << "assign-move-ctor" << endl;
		return *this;
	};
	int get()
	{
		return m_data;
	}

	~Heap1()
	{
		cout << "dtor" << endl;
	}
private:
	int m_data;
};

void heap_tc_main()
{
	heap <int> hp;
	vectorClass<Heap1> v;
	v.push(Heap1(10));
	v.push(Heap1(20));
	v.push(Heap1(30));
	v.push(Heap1(40));
	v.push(Heap1(50));

	cout << "Vector size : "
		<< v.size() << endl;
	cout << "Vector capacity : "
		<< v.getcapacity() << endl;

	v.push(100, 1);
	cout << "Vector elements : ";
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.get(i)->get() << " ";
	}
}