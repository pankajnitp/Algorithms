#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;

struct _node {
	_node *child[26];
	unsigned char* name;
};

_node* trieNode = NULL;

int _strlen(unsigned char* name)
{
	int len = 0;
	while (*name++)
		len++;
	return len;
}

void _memcpy(unsigned char* to, unsigned char* from)
{
	while (*to++ = *from++);
}

void AddInTrie(_node** head, unsigned char* from, unsigned char* to)
{
	if (*head == NULL)
		*head = (_node*)calloc(1, sizeof(_node));
	_node* ptr = *head;

	int len = _strlen(from);
	for (int i = 0; i < len; i++)
	{
		if(ptr->child[from[i]-'a'] == NULL)
			ptr->child[from[i] - 'a'] = (_node*)calloc(1, sizeof(_node));
		ptr = ptr->child[from[i] - 'a'];
	}
	if (ptr->name)
		free(ptr->name);
	ptr->name = (unsigned char*)malloc(sizeof(to) + 1);
	_memcpy(ptr->name, to);
}

unsigned char* FindInTrie(_node* head, unsigned char* from)
{
	int len = _strlen(from);
	_node* ptr = head;
	for (int i = 0; i < len; i++)
	{
		if (ptr->child[from[i] - 'a'] == NULL)
			return NULL;
		ptr = ptr->child[from[i] - 'a'];
	}
	return ptr->name;
}

int main()
{
	int T, N, Q;
	unsigned char from[11], to[11];
	unsigned char* toName = NULL;
	freopen("dictionary.txt", "r", stdin);
	cin >> T;
	
	while (T--)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> from >> to;
			AddInTrie(&trieNode, from, to);
		}
		cin >> Q;
		for (int i = 0; i < Q; i++)
		{
			cin >> from;
			toName = FindInTrie(trieNode, from);
			cout << toName << endl;
		}
	}
	return 0;
}
