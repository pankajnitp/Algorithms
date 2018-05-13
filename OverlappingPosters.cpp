#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;

int T, N, _count;

struct _area
{
	int fromA, toB;
} poster[40000];

struct _record
{
	int from, to, val;
} record[10000000];

char _hash[40000];

int VisiblePosters()
{
	int a, b;
	for (int i = N - 1, j=1; i >= 0; i--, j++)
	{
		a = poster[i].fromA;
		b = poster[i].toB;
		for (int k = a; k <= b; )
		{
			if (!record[k].val || _hash[record[k].val]==0)
			{
				record[k].from = a;
				record[k].to = b;
				record[k].val = j;
				_hash[j] = 1;
				k++;
			}
			else
			{
				k = record[k].to + 1;
			}
		}
		if (_hash[j]) _count++;
	}
	return 0;
}

int main()
{
	freopen("poster.txt", "r", stdin);
	cin >> T;

	while (T--)
	{
		_count = 0;
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> poster[i].fromA >> poster[i].toB;

		VisiblePosters();
		cout << _count << endl;
		for (int i = 0; i < 40000; i++)
			_hash[i] = 0;
	}
	return 0;
}
