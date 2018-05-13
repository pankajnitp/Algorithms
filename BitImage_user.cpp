#define MAX_ITEMS			100
#define WIDTH				200
#define HEIGHT				200
#define SCREEN_WIDTH		1000
#define SCREEN_HEIGHT		1000

#define FOR(i, init, cnt) for(int i=init; i< cnt; i++)
#define MAXN				201
#define INF					0x3f3f3f3fL
#define DSIZE				225000

int W, H;

char Bgrid[MAXN][MAXN];
char DArr[DSIZE];
char type;
int DIndex = 0;
int DReadIdx = 0;
int DLen = 0;
int DId = 0;
char rawImage[MAX_ITEMS][WIDTH][HEIGHT];
char prevState[MAX_ITEMS][WIDTH][HEIGHT];

enum blendMode {
	BLEND_OR,
	BLEND_AND,
};

struct imageProperty {
	bool		bShown;
	int			xCoord, yCoord;
	int			width, height;
	blendMode	rop;
} imageProp[MAX_ITEMS];

int strLength(char* str)
{
	int len = 0;
	while (*str++) ++len;
	return len;
}

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		Bgrid[i][j] = 0;

	FOR(i, 0, DSIZE)
		DArr[i] = 0;

	DIndex = 0;
	DReadIdx = 0;
}

void D2B(int x1, int y1, int x2, int y2)
{
	int w = x2 - x1 + 1;
	int h = y2 - y1 + 1;

	if (DLen == DReadIdx)
		return;

	if (w == 0 || h == 0)
		return;

	char c = DArr[DReadIdx++];
	
	if (c == '0' || c == '1')
	{
		FOR(i, 0, h)
			FOR(j, 0, w)
			rawImage[DId][y1 + i][x1 + j] = c;

		return;
	}
	else if (c == 'D')
	{
		D2B(x1,			y1,			x2 - (w / 2),	y2 - (h / 2));
		D2B(x2-(w/2)+1,	y1,			x2,				y2 - (h / 2));
		D2B(x1,			y2-(h/2)+1,	x2 - (w / 2),	y2);
		D2B(x2-(w/2)+1, y2-(h/2)+1,	x2,				y2);
	}
}

void init(char screen[][1000], int w, int h)
{
	FOR(i, 0, h)
		FOR(j, 0, w)
		screen[i][j] = '0';
}
void create(char *img, int imageid, int w, int h)
{
	int i = 0;

	while(DArr[i++] = *img++)
	{
	}
	DLen = i;
	DReadIdx = 0;
	DId = imageid;
	imageProp[imageid].width = w;
	imageProp[imageid].height = h;

	D2B(0, 0, w - 1, h - 1);
}

void draw(int id, int x, int y, int mode, char screen[][1000])
{
	int hLimit = (x + imageProp[id].width) > SCREEN_WIDTH ? SCREEN_WIDTH : (x + imageProp[id].width);
	int vLimit = (y + imageProp[id].height) > SCREEN_HEIGHT ? SCREEN_HEIGHT : (y + imageProp[id].height);

	int x1 = x;
	int y1 = y;

	if (mode == BLEND_OR)
	{
		FOR(j, y, vLimit)
		{
			FOR(i, x, hLimit)
			{
				if (i < 0 || j < 0)
					continue;
				prevState[id][j - y1][i - x1] = screen[j][i];
				screen[j][i] |= rawImage[id][j - y1][i - x1];
			}
		}
		imageProp[id].rop = BLEND_OR;
	}
	else
	{
		FOR(j, y, vLimit)
		{
			FOR(i, x, hLimit)
			{
				if (i < 0 || j < 0)
					continue;
				prevState[id][j - y1][i - x1] = screen[j][i];
				screen[j][i] &= rawImage[id][j - y1][i - x1];
			}
		}
		imageProp[id].rop = BLEND_AND;
	}
	imageProp[id].xCoord = x;
	imageProp[id].yCoord = y;
	imageProp[id].bShown = true;
}

void showImage(int id, char screen[][1000])
{
	if (imageProp[id].bShown)
	{
		draw(id, imageProp[id].xCoord, imageProp[id].yCoord, imageProp[id].rop, screen);
	}
}

void hideImage(int id, char screen[][1000])
{
	if (!imageProp[id].bShown) 
	{
		return;
	}
	int xS = imageProp[id].xCoord;
	int xE = (xS + imageProp[id].width) > SCREEN_WIDTH ? SCREEN_WIDTH : (xS + imageProp[id].width);
	int yS = imageProp[id].yCoord;
	int yE = (yS + imageProp[id].height) > SCREEN_HEIGHT ? SCREEN_HEIGHT : (yS + imageProp[id].height);

	int xImage = xS;
	int yImage = yS;

	if (imageProp[id].rop == BLEND_OR)
	{
		FOR(j, yS, yE)
		{
			FOR(i, xS, xE)
			{
				if (i < 0 || j < 0)
					continue;
				if (rawImage[id][j - yImage][i - xImage] == screen[j][i])
				{
					if(screen[j][i])
						screen[j][i] = prevState[id][j - yImage][i - xImage];
				}
			}
		}
	}
	else
	{
		FOR(j, yS, yE)
		{
			FOR(i, xS, xE)
			{
				if (i < 0 || j < 0)
					continue;
				screen[j][i] |= prevState[id][j - yImage][i - xImage];
			}
		}
	}
}
