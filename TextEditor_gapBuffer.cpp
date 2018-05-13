#include <stdio.h>
#define SZ 1000000
#define SELECT 5000

char leftArray[SZ], rightArray[SZ];
int leftCount, rightCount;
int cursorPos;
char select[SELECT];

void printArray() {

	for (register int i = 0; i < leftCount; i++) {
		printf("%c", leftArray[i]);
	}

	for (register int i = rightCount - 1; i >= 0; i--) {
		printf("%c", rightArray[i]);
	}
	printf("\n");
}

void adjust(int pos) {

	while (leftCount > pos) {
		rightArray[rightCount++] = leftArray[--leftCount];
	}

	while (leftCount < pos) {
		leftArray[leftCount++] = rightArray[--rightCount];
	}
	cursorPos = pos;
}

void init() {

	cursorPos = leftCount = rightCount = 0;
}

void addWord(char word[], int len) {

	//adjust(cursorPos);

	for (register int i = 0; i < len; i++) {
		leftArray[leftCount++] = word[i];
	}
	leftArray[leftCount] = 0;
	cursorPos += len;
}

void addBackSpace() {

	adjust(cursorPos);
	leftCount--;
}

void moveCurson(int newPosition) {

	cursorPos = newPosition;
}

void selectText(int from, int to)
{
	to = to < (leftCount + rightCount) ? to : (leftCount + rightCount);
	int length = to - from + 1;

	adjust(cursorPos);

	int k = 0;
	int l = 0;
	while (k + from < leftCount && k < length) {
		select[k] = leftArray[from + k];
		k++;
	}

	length -= k;
	while (l < length) {
		select[k++] = rightArray[rightCount - 1 - l];
		l++;
	}
}

void cutSelection()
{

}

void pasteSelection()
{

}

void subString(int pos, int length, char result[]) {

	adjust(cursorPos);

	int k = 0;
	int l = 0;
	while (k + pos < leftCount && k < length) {
		result[k] = leftArray[pos + k];
		k++;
	}

	length -= k;
	while (l < length) {
		result[k++] = rightArray[rightCount - 1 - l];
		l++;
	}
}
int _hash(int a)
{
a = (a ^ 61) ^ (a >> 16);
a = a + (a << 3);
a = a ^ (a >> 4);
a = a * 0x27d4eb2d;
a = a ^ (a >> 15);
return a;
}

char result[1000];


int main()
{
	init();
	addWord("Hello", 5);
	printArray();
	addBackSpace();

	addWord("!!", 2);
	moveCurson(6);
	addWord("World", 5);
	printArray();

	subString(3, 4, result);
	return 0;
}
