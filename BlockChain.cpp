#pragma GCC optimize ("-Ofast")
#include <iostream>
using namespace std;

#include <stdio.h>

#define MAX_BLOCKS 75000
#define MAX_CHILD 20
#define MAX_TXN 16
#define MAX_SERVERS 5
#define MAX_BLOCKDATA 400000

static int _blockId;
static int _numServer;

struct _node {
	char	_parenthash[4];
	int		_child[MAX_CHILD + 1];
	short	_amount[MAX_TXN];
	int		_count;
} nodePool[MAX_BLOCKS];

struct _trieEntry{
	_trieEntry* child[16];
	int			_id;
} *trieHead = (_trieEntry*)calloc(1, sizeof(_trieEntry));;

inline int redirect(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - 48;
	else
		return ch - 'a';
}

void insertTrie(char* hash, int idx)
{
	_trieEntry* ptr = trieHead;
	int i = 0;
	for (; i < 8; i++)
	{
		if (ptr->child[redirect(hash[i])] == NULL)
			ptr->child[redirect(hash[i])] = (_trieEntry*)calloc(1, sizeof(_trieEntry));
		ptr = ptr->child[redirect(hash[i])];
	}
	ptr->_id = idx;
	nodePool[idx]._count++;
}

void calHash(char *blockdata, int len, char hash[8])
{

}

void initServers(int M, char blockdata[MAX_SERVERS][MAX_BLOCKDATA])
{
	int length, blockLen;
	int k, j;
	char hash[8];
	_blockId = 0;
	_numServer = M >> 1;

	for (int i = 0; i < M; i++)
	{
		k = 0, j = 4;
		length = (blockdata[i][k] << 24) | (blockdata[i][k + 1] << 16) | (blockdata[i][k + 2] << 8) | (blockdata[i][k + 3]);
		while (j < length)
		{
			blockLen = 7 + (3 * blockdata[i][j + 6]);
			calHash(&blockdata[i][j], length, hash);
			nodePool[i]._parenthash[0] = blockdata[i][j], nodePool[i]._parenthash[1] = blockdata[i][j + 1];
			nodePool[i]._parenthash[2] = blockdata[i][j + 2], nodePool[i]._parenthash[3] = blockdata[i][j + 3];
			j += blockLen;
			insertTrie(hash, _blockId++);
		}
	}

	// Find valid blocks and prepare parent-child relations
	for (int i = 0; i < _blockId; i++)
	{
		if (nodePool[i]._count >= _numServer)
		{

		}
	}
}

int main()
{
	return 0;
}
