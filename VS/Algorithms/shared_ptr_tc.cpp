#include<iostream>
#include "testcases.h"

using namespace std;

void shared_ptr_tc_main()
{
	Shared_ptr<int> ptr1(new int(151));
	cout << "--- Shared pointers ptr1, ptr2 ---\n";
	{
		Shared_ptr<int> ptr2 = ptr1;
		cout << ptr1;
		cout << ptr2;
	}
	cout << ptr1;
}