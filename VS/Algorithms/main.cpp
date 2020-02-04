#include<iostream>
#include "shared_ptr.h"
#include "math_util.h""

using namespace std;

int main()
{
	Element<int> el1(3);
	Element<int> el2(5);

	outer(17, 29);
	cout << el2 + el1 << endl;

	Shared_ptr<int> ptr1(new int(151));
	cout << "--- Shared pointers ptr1, ptr2 ---\n";
	{
		Shared_ptr<int> ptr2 = ptr1;
		cout << ptr1;
		cout << ptr2;
	}
	cout << ptr1;

	return 0;
}