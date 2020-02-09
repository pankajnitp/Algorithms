#define MAX_HEADS 10000
#define MAX_GRID 3000

char grid[MAX_HEADS + 1][MAX_HEADS + 1];
char pending[MAX_HEADS + 1][MAX_HEADS + 1];
int gridSize;
int lastTime;

struct _Coord
{
	short x, y;
};

class _WireQueue {
	_Coord qData[MAX_HEADS];
	short front, rear;
public:
	void init()
	{
		front = rear = 0;
	}
	void pushBack(_Coord xy)
	{
		qData[rear++] = xy;
		if (rear >= MAX_HEADS)
			rear = 0;
	}
	_Coord popFront()
	{
		_Coord ret = qData[front++];
		if (front >= MAX_HEADS)
			front = 0;
		return ret;
	}
	int getSize()
	{
		return (rear - front);
	}
};

_WireQueue headQueue;

void Init(int N)
{
	gridSize = N;
	lastTime = 0;
	for (register int i = 0; i < N; i++)
	{
		for (register int j = 0; j < N; j+=4)
		{
			grid[i][j] = 0x00000000;
			pending[i][j] = 0x00000000;
		}
	}
	headQueue.init();
}

void AddWire(int sx, int sy, int dir, int len)
{
	switch (dir)
	{
	case 1:
		for (register int i = 0; i < len; i++)
			grid[sy][sx + i] = 'C';
		break;
	case 2:
		break;
		for (register int i = 0; i < len; i++)
			grid[sy + i][sx] = 'C';
	case 3:
		grid[sy][sx] = 'C';
		break;
	default:
		break;
	}
}

int xInc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int yInc[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

int Gogo(int second)
{
	_WireQueue pendingHeadQ, pendingTailQ, pendingCondQ;
	int headSize;
	_Coord curHead, newHead, newTail, newCond;
	int nX, nY;
	int surroundingHead;

	pendingHeadQ.init();
	pendingTailQ.init();
	pendingCondQ.init();

	for (int i = 0; i < (second - lastTime); i++)
	{
		headSize = headQueue.getSize();
		for (register int j = 0; j < headSize; j++)
		{
			curHead = headQueue.popFront();
			for (register int dir = 0; dir < 8; dir++)
			{
				nX = curHead.x + xInc[dir];
				nY = curHead.y + yInc[dir];

				surroundingHead = 0;

				if (nX >= 0 && nX < MAX_GRID && nY >= 0 && nY < MAX_GRID && grid[nY][nX] == 'C' && pending[nY][nX] != 'y')
				{

					for (register int dir2 = 0; dir2 < 8; dir2++)
					{
						if (grid[nY + yInc[dir2]][nX + xInc[dir2]] == 'H')
							surroundingHead++;
					}
					if (surroundingHead < 3)
					{
						newHead.x = nX;
						newHead.y = nY;
						pendingHeadQ.pushBack(newHead);
					}
				}
			}
			pendingTailQ.pushBack(curHead);
		}
		while (pendingCondQ.getSize())
		{
			newCond = pendingCondQ.popFront();
			grid[newCond.y][newCond.x] = 'C';
		}
		while (pendingTailQ.getSize())
		{
			newTail = pendingTailQ.popFront();
			pendingCondQ.pushBack(newTail);
			grid[newTail.y][newTail.x] = 'T';
		}
		while (pendingHeadQ.getSize())
		{
			newHead = pendingHeadQ.popFront();
			headQueue.pushBack(newHead);
			grid[newHead.y][newHead.x] = 'H';
		}
	}
	int ret = headQueue.getSize();
	return ret;
}

#include<iostream> 
using namespace std;

class Final;  // The class to be made final 

class MakeFinal // used to make the Final class final 
{
private:
	MakeFinal() { cout << "MakFinal constructor" << endl; }
	friend class Final;
};

class Final : private MakeFinal
{
public:
	Final() { cout << "Final constructor" << endl; }
};

/*
class Derived : public Final // Compiler error 
{
public:
	Derived() { cout << "Derived constructor" << endl; }
};
*/
#if 0
class Base { 
public:
	Base() {};
	virtual ~Base() {};
};
class Derived : public Base { };
int main() {
	Derived d; 
	Base *b = &d;
	Derived *ptr = dynamic_cast <Derived*>(b); 
	if (ptr)
	{

	}
	else
	{

	}
}

#endif

extern int a;
static int *b;
const static int c = 10;
char *d = "Pankaj";

inline int func(int k)
{
	int l = a + k;
	return l;
}

int main()
{
	int e = a + c;
	volatile int j = 0;

	b = (int*)calloc(5, sizeof(int));
	b[10] = 33;
	d[0] = 'K';

	for (register int i = 0; i < 10; i++)
	{
		j = func(j);
	}
	return 0;
}
