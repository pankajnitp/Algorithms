#include<string.h>
#include<stdio.h>
#include <iostream>
using namespace std;

//#define _GENERATE_TC_
#define _DEBUG_

#define SCREEN_WIDTH	1000
#define SCREEN_HEIGHT	1000
#define MAX_ITEMS		100
#define WIDTH			200
#define HEIGHT			200
#define DSIZE			225000
#define FOR(i, init, cnt)	for(int i=init; i< cnt; i++)
#define THRESHOLD		0x07FFFFFF

int height, width;

int ORG[MAX_ITEMS];

static char screen[1000][1000];
static int point;
char temp1[225000];

extern void init(char screen[][1000], int w, int h);
extern void create(char *img, int imageid, int w, int h);
extern void draw(int imageid, int x, int y, int mode, char screen[1000][1000]);
extern void showImage(int id, char screen[][1000]);
extern void hideImage(int id, char  screen[][1000]);

enum {
	INIT = 1,
	CREATE,
	DRAW,
	SHOW,
	HIDE,
};

static int GetHashValue()
{
	unsigned int count = 1;
	unsigned int sum = 0;
	FOR(i, 0, 1000)
	{
		FOR(j, 0, 1000)
		{
			sum += ((screen[i][j] - 48));// *count);
			sum &= THRESHOLD;
			count++;
		}
	}
	return sum;
}

static void run()
{
	int numCmds;
	int blendCnt = 0;
	scanf("%d", &numCmds);
	//cin >> numCmds;

	FOR(line, 0, numCmds)
	{
		int command, imageid;
		int x, y, mode;
		int calHash, realHash;
		cin >> command;

		switch (command)
		{
		case INIT:
			init(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		case CREATE:
			//scanf("%d %d", &imageid, &img.type);
			cin >> imageid >> height >> width;
			char ch;
			cin.getline(temp1, 2);
			cin.getline(temp1, DSIZE);
			create(temp1, imageid, width, height);
			break;
		case DRAW:
			cin >> imageid >> x >> y >> mode >> realHash;
			draw(imageid, x, y, mode, screen);
			calHash = GetHashValue();
			if (calHash == realHash)
				point++;
			else
				point = point;
			break;
		case SHOW:
			cin >> imageid >> realHash;
			showImage(imageid, screen);
			calHash = GetHashValue();
			if (calHash == realHash)
				point++;
			else
				point = point;
			break;
		case HIDE:
			cin >> imageid >> realHash;
			hideImage(imageid, screen);
			calHash = GetHashValue();
			if (calHash == realHash)
				point++;
			else
				point = point;
			break;
		}

	}
}

static void generateTC()
{
	int numDs;
	cin >> numDs;

	int numOps[] = { 1, 2, 4, 10, 25, 50, 100 };
	int count = 7, ranNum, randRop, randDis;

	int command, imageid;
	int w, h, x_coord, y_coord, mode;
	int calHash, realHash;
	char ch;
	int idInc = 0;

	int *drawOrder;
	int *displayOrder;
	cout << count << endl;
	FOR(i, 0, count)
	{
		idInc = 0;
		cout << (3 * numOps[i]) + 1 << endl;
		cout << 1 << endl; //Init
		init(screen, SCREEN_WIDTH, SCREEN_HEIGHT);

		drawOrder = (int*)calloc(numOps[i], sizeof(int));
		displayOrder = (int*)calloc(numOps[i], sizeof(int));

		FOR(j, 0, numOps[i]) //Create
		{
			cin >> ch >> h >> w;
			cout << 2 << " " << idInc++ << " " << h << " " << w << endl;
			cin.getline(temp1, 2);
			cin.getline(temp1, DSIZE);
			cout << temp1 << endl;
			create(temp1, idInc - 1, w, h);
		}
		FOR(j, 0, numOps[i]) //Draw
		{
			x_coord = rand() % 1400;
			y_coord = rand() % 1400;
			x_coord -= 200;
			y_coord -= 200;
			randRop = rand() % 2;

			ranNum = rand() % numOps[i];
			while(drawOrder[ranNum])
			{
				ranNum = rand() % numOps[i];
			}
			drawOrder[ranNum] = true;
			draw(ranNum, x_coord, y_coord, randRop, screen);
			calHash = GetHashValue();

			cout << "3 " << ranNum << " " << x_coord << " " << y_coord << " " << randRop << " " << calHash << endl;
		}

		FOR(j, 0, numOps[i]) //Show/Hide
		{
			randDis = rand() % numOps[i];
			while (displayOrder[randDis])
			{
				randDis = rand() % numOps[i];
			}
			displayOrder[randDis] = true;

			int showHide = rand() % 2;
			if (showHide == 1)
			{
				showImage(randDis, screen);
				calHash = GetHashValue();
				cout << "4 " << randDis << " " << calHash << endl;
			}
			else
			{
				hideImage(randDis, screen);
				calHash = GetHashValue();
				cout << "5 " << randDis << " " << calHash << endl;
			}
		}

		free (drawOrder);
		free(displayOrder);
	}
}

int main()
{
#ifdef _GENERATE_TC_
	freopen("input_image.txt", "r", stdin);
	freopen("input_TCs.txt", "w", stdout);
	generateTC();
#else
	freopen("input_TCs.txt", "r", stdin);
	freopen("output_image.txt", "w", stdout);	
	int T;
	cin >> T;
	while (T--)
	{
		run();
		cout << point << endl;
		point = 0;
	}
	if (point == 100)
		cout << "Pass";
	else
		cout << "Fail";
#endif
	return 0;
}

