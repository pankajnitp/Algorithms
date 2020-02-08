#include<iostream>
#include "testcases.h"

using namespace std;

class Counter1 {
public:
	// Constructor
	Counter1() {
		m_data = 0;
		cout << "default-ctor"<<endl;
	}

	Counter1(int data){
		m_data = data;
		cout << "ctor"<<endl;
	}

	Counter1(const Counter1& rhs) 
	{ 
		this->m_data = rhs.m_data;
		cout << "copy-ctor"<<endl; 
	};
	Counter1(const Counter1&& rhs) 
	{ 
		this->m_data = rhs.m_data;
		cout << "copy-move-ctor" << endl; 
	};
	Counter1& operator=(const Counter1& rhs) 
	{ 
		this->m_data = rhs.m_data;
		cout << "assign-ctor" << endl;
		return *this;
	};
	Counter1& operator=(const Counter1&& rhs) 
	{ 
		this->m_data = rhs.m_data;
		cout << "assign-move-ctor" << endl;
		return *this;
	};
	int get()
	{
		return m_data;
	}

	~Counter1()
	{
		cout << "dtor" << endl;
	}
private:
	int m_data;
};

void vector_tc_main()
{
	vectorClass<Counter1> v;
	v.push(Counter1(10));
	v.push(Counter1(20));
	v.push(Counter1(30));
	v.push(Counter1(40));
	v.push(Counter1(50));

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