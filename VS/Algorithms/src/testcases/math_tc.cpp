#include<iostream>
#include "testcases.h"
using namespace std;

void inner(int &a, int &b)
{
	cout << "#1" << endl;
}
void inner(int &&a, int &&b)
{
	cout << "#2" << endl;
}

template <typename T1, typename T2>
void outer(T1&& t1, T2&& t2)
{
	inner(std::forward<T1>(t1), std::forward<T2>(t2));
	//inner(t1, t2);
}

void math_tc_main()
{
	Element<int> el1(3);
	Element<int> el2(5);

	outer(17, 29);
	cout << el2 + el1 << endl;
}