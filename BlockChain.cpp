#pragma GCC optimize ("-Ofast")
#include <iostream>
using namespace std;

#include <stdio.h>

struct _node {
	int	_child[20];
	short	_amount[16];
} nodePool[15000];

struct _trieEntry{
	_trieEntry* child[16];
	int		_id;
} *trieHead = NULL;

void insertTrie(char* hash)
{
	_trieEntry* ptr = trieHead;
	
}
void init()
{
	trieHead = (_trieEntry*) calloc(1, sizeof(_trieEntry));
}

int main()
{
	return 0;
}
