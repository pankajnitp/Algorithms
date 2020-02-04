#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAXMEMORY 65536
#define MAXLEN 12

static unsigned char memory[MAXMEMORY];

bool memread(unsigned char buf[], int pos, int len)
{
	if (pos < 0 || len <= 0 || pos + len >= MAXMEMORY)
		return false;
	for (int i = 0; i < len; i++)
	{
		buf[i] = memory[pos + i];
	}
	return true;
}

bool memwrite(unsigned char buf[], int pos, int len)
{
	if (pos < 0 || len <= 0 || pos + len >= MAXMEMORY)
		return false;

	for (int i = 0; i < len; i++)
	{
		memory[pos + i] = buf[i];
	}
	return true;
}

static bool mstrcmp(unsigned char *a, unsigned char *b)
{
	while (*a && *a == *b)
	{
		++a; ++b;
	}
	return *a == *b;
}

extern bool Init(int N);
extern void Add(unsigned char in_key[MAXLEN + 1], unsigned char in_value[MAXLEN + 1]);
extern void Del(unsigned char in_key[MAXLEN + 1]);
extern void Get(unsigned char in_key[MAXLEN + 1], unsigned char out_value[MAXLEN + 1]);
extern void GetKey(unsigned char in_value[MAXLEN + 1], unsigned char out_key[MAXLEN + 1]);

#define INIT_CODE 50
#define ADD_CODE 100
#define DEL_CODE 200
#define GET_CODE 300
#define GET_KEY_CODE 400

int main()
{
	freopen("input_sangrahak.txt", "r", stdin);

	unsigned char key[MAXLEN + 1];
	unsigned char value[MAXLEN + 1];
	unsigned char key22[MAXLEN + 1];
	unsigned char value22[MAXLEN + 1];

	int TC = 0;
	int score = 0;
	int total_score = 0;
	bool bOkay = false;

	while (1)
	{
		int N;
		int code = 99;
		int ret = scanf("%d", &code);
		if (ret != 1)
		{
			total_score += score;
			break;
		}

		switch (code)
		{
		case INIT_CODE:
			scanf("%d", &N);
			++TC;
			bOkay = Init(N);

			total_score += score;
			score = 100;
			if (!bOkay)
				score = 0;
			break;
		case ADD_CODE:
			scanf("%s%s", key, value);
			if (bOkay)
				Add(key, value);
			break;
		case DEL_CODE:
			scanf("%s", key);
			if (bOkay)
				Del(key);
			break;
		case GET_CODE:
			scanf("%s%s", key, value);
			if (bOkay)
			{
				Get(key, value22);
				if (!mstrcmp(value22, value))
					score = 0;
			}
			break;
		case GET_KEY_CODE:
			scanf("%s%s", value, key);
			if (bOkay)
			{
				GetKey(value, key22);
				if (!mstrcmp(key, key22))
				{
					score = 0;
				}
			}
			break;
		default:
			break;
		}
	}
	printf("Total score %d\n", total_score / TC, TC);
	return 0;
}