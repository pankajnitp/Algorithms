#define MAXENTRY 2400
#define MAXLEN 12
#define ELEMENTSIZE 27
#define MAXHASH MAXENTRY*ELEMENTSIZE

extern bool memread(unsigned char buf[], int pos, int len);
extern bool memwrite(unsigned char buf[], int pos, int len);

int genHashKey(unsigned char *str)
{
	unsigned int hash = 5381;
	char ch;
	int i = 0;
	while (ch = str[i++])
	{
		hash += (hash << 5) + hash + ch;
	}
	return (hash & 0x7FFFFFFF ) % MAXENTRY;
}

int getLength(unsigned char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}

bool Init(int N)
{
	unsigned char buf[1];
	buf[0] = 0;
	for (register int i = 0; i < MAXENTRY; i += 27)
	{
		memwrite(buf, i, 1);
	}
	return true;
}

void Add(unsigned char key[], unsigned char value[])
{
	int hashKey = genHashKey(key);
	int lenKey = getLength(key);
	int lenVal = getLength(value);

	unsigned char buf[1 + 2 + MAXLEN*2];
	int pos = hashKey * ELEMENTSIZE;

	memread(buf, pos, 1);
	while (int(buf[0]) != 0)
	{
		pos += ELEMENTSIZE;
		if (pos >= MAXHASH)
			pos = 0;
		memread(buf, pos, 1);
	}

	buf[0] = 1;
	buf[1] = lenKey; //Key length
	for (int i = 0; i < lenKey; i++)
	{
		buf[2 + i] = key[i];
	}

	buf[1 + 1 + 12] = lenVal;
	for (int i = 0; i < lenVal; i++)
	{
		buf[15 + i] = value[i];
	}
	memwrite(buf, pos, 27);
}

void Del(unsigned char key[])
{
	int hashKey = genHashKey(key);
	int lenKey = getLength(key);
	
	unsigned char buf[14];
	int pos = hashKey * ELEMENTSIZE;
	int matched = 0;

	memread(buf, pos, 2);
	while (1)
	{
		if (int(buf[0]) != 1 || int(buf[1]) != lenKey)
		{
			pos += ELEMENTSIZE;
			if (pos >= MAXHASH)
				pos = 0;
			memread(buf, pos, 2);
		}
		else
		{
			memread(buf, pos + 2, MAXLEN); /////////////////////////////
			for (matched = 0; matched < lenKey; matched++)
			{
				if (buf[matched] != key[matched])
					break;
			}
			if (matched == lenKey)
			{
				buf[0] = 0;
				memwrite(buf, pos, 1);
				return;
			}
		}
	}
}

void Get(unsigned char key[], unsigned char value[])
{
	int hashKey = genHashKey(key);
	int lenKey = getLength(key);

	unsigned char buf[27];
	int pos = hashKey * ELEMENTSIZE;
	int matched = 0;
	memread(buf, pos, 2);
	while (1)
	{
		if (int(buf[0]) != 1 )
		{
			pos += ELEMENTSIZE;
			if (pos >= MAXHASH)
				pos = 0;
			memread(buf, pos, 2);
		}
		else
		{
			if (int(buf[1]) == lenKey) 
			{
				memread(buf, pos + 2, MAXLEN); /////////////////////////////
				for (matched = 0; matched < lenKey; matched++)
				{
					if (buf[matched] != key[matched])
						break;
				}
				if (matched == lenKey)
				{
					memread(buf, pos + 14, 13);////// 1 + 12
					for (int i = 0; i<int(buf[0]); i++)
					{
						value[i] = buf[1 + i];
					}
					value[int(buf[0])] = '\0';
					return;
				}
			}
		}
	}
}

void GetKey(unsigned char value[], unsigned char key[])
{
	int lenVal = getLength(value);
	unsigned char buf[15];
	int pos = 0;
	int matched = 0;

	memread(buf, pos, 2);
	while (1)
	{
		if (int(buf[0]) != 1 )
		{
			pos += ELEMENTSIZE;
			if (pos >= MAXHASH)
				pos = 0;
			memread(buf, pos, 1);
		}
		else
		{
			memread(buf, pos + 14, 1); /////////////////////////////
			if (int(buf[0]) != lenVal)
			{
				pos += ELEMENTSIZE;
				if (pos >= MAXHASH)
					pos = 0;
				memread(buf, pos, 1);
			}
			else
			{
				memread(buf, pos + 15, lenVal);
				for (matched = 0; matched < lenVal; matched++)
				{
					if (buf[matched] != value[matched])
						break;
				}
				if (matched == lenVal)
				{
					memread(buf, pos + 1, 13);
					for (int i = 0; i<int(buf[0]); i++)
					{
						key[i] = buf[1 + i];
					}
					key[int(buf[0])] = '\0';
					return;
				}
				pos += ELEMENTSIZE;
				if (pos >= MAXHASH)
					pos = 0;
				memread(buf, pos, 1);
			}
		}
	}
}
