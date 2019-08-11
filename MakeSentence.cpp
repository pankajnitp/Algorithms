#include <iostream>
#include <stdio.h>
#define NULL 0

static int memCounter;

struct _LL {
	int hashID;
	_LL* next;
};

static _LL *headLL, *tailLL;
struct _word
{
	char str[11];
	int hashVal;
	int length;
} words[30000];

static int hashAllocator;
struct _hashTable
{
	int wordID;
	int firstLink;
	int lastLink;
	int isFilled;
	_LL* ptrLL;
} hashTable[60000];

void init()
{
	memCounter = hashAllocator = 0;
	headLL = tailLL = NULL;
}

int getHashKey(char str[])
{
	int hash = 5381;
	char ch;
	while (ch = *str++)
	{
		hash = (hash * 33) + ch;
	}
	return hash;
}

int addInHashTable(char str[])
{

	return 0;
}

void appendWord(char str[])
{
	int IDx = addInHashTable(str);
	_LL* ptr = (_LL*)calloc(1, sizeof(_LL));

	if (headLL == NULL)
	{
		headLL = tailLL = ptr;
	}
	else
	{
		tailLL->next = ptr;
		tailLL = ptr;
	}
}

void removeKthWord(int K)
{
	// 1->2->3->4
	_LL* ptr = headLL;
	for (int i = 0; i < (K - 2); i++)
	{
		ptr = ptr->next;
	}
	ptr->next = ptr->next->next;
}

void replaceWord(char before[], char after[])
{
	int idx_new = addInHashTable(after);

	// find wordID of before str
	int idx_old = addInHashTable(before);

	int key_new = getHashKey(after);
	int len_new = strlen(after);

	strcpy(words[idx_old].str, after);
	words[idx_old].hashVal = key_new;
	words[idx_old].length = len_new;
	// something smelling ....
}

char getKthChar(int K)
{
	//(0, n1)->(1, n2)->(2, n3)->(3, n4)
	_LL* ptr = headLL;
	int sum = 0;
	int wordID = hashTable[ptr->hashID].wordID;

	while ((sum + words[wordID].length) < K)
	{
		sum += words[wordID].length + 1;
		ptr = ptr->next;
		wordID = hashTable[ptr->hashID].wordID;
	}
	return words[wordID].str[K - sum -1];
}