// Input String: Sky is the limit
// Output String: limit the is Sky
// kkadakia@mathworks.com


#include <iostream>
using namespace std;
int mlen(char* str)
{
	int count = 0;
	while (*str++)
	{
		count++;
	}
	return count;
}

void reverse(char * str)
{
	char* temp = str;
	int len = mlen(temp);
	int i = 0;
	for (i = len - 1; i >= 0; i--)
	{
		if (temp[i] == ' ')
		{
			cout << &temp[i + 1] << " ";
			temp[i] = '\0';
		}
	}
	cout << &temp[i + 1];
}

#include <iostream>
using namespace std;

int main() {
	char str[] = "Sky is the limit";
	reverse(str);
	return 0;
}
