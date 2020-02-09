#define BASE_NUMBER 16384
#define NULL 0

struct _songChunk {
	int start;
	short songID;
	short position;
	int end;
};

struct _songList
{
	_songChunk* node;
};

_songChunk songChunkPool[193 * 10001];
_songList gSongList[193 * 10001];
short songData[10001][200];

int poolID, listID;
bool isUpdate;

void init(int n)
{
	poolID = listID = 0;
	isUpdate = false;
}

void swapChunk(int a, int b)
{
	_songList temp;
	temp = gSongList[a];
	gSongList[a] = gSongList[b];
	gSongList[b] = temp;
}
int quickSort(int l, int h)
{
	int i = l - 1;
	int pivot = gSongList[h].node->start;

	for (int j = l; j < h; j++)
	{
		if (gSongList[j].node->start < pivot)
		{
			i++;
			swapChunk(i, j);
		}
	}
	swapChunk(i+1, h);
	return i + 1;
}

void quickSortUtil(int l, int h)
{
	int q;
	if (l < h)
	{
		q = quickSort(l, h);
		quickSortUtil(l, q - 1);
		quickSortUtil(q + 1, h);
	}
}
void send_music(int music_id, int music_len, int mdata[])
{
	int chunkSum = 0;

	for (int i = 0; i < 8; i++)
	{
		chunkSum += mdata[i] + BASE_NUMBER;
		songData[music_id][i] = mdata[i];
	}
	songChunkPool[poolID].start = chunkSum - (128 * 8);
	songChunkPool[poolID].end = chunkSum + (127 * 8);
	songChunkPool[poolID].songID = music_id;
	songChunkPool[poolID].position = 0;
	gSongList[listID].node = &songChunkPool[poolID];
	poolID++;
	listID++;

	for (register int i = 8; i < music_len; i++)
	{
		chunkSum -= (mdata[i-8]);
		chunkSum += (mdata[i]);
		songChunkPool[poolID].start = chunkSum - (128 * 8);
		songChunkPool[poolID].end = chunkSum + (127 * 8);
		songChunkPool[poolID].songID = music_id;
		songChunkPool[poolID].position = i-7;
		songData[music_id][i] = mdata[i];

		gSongList[listID].node = &songChunkPool[poolID];
		poolID++;
		listID++;
	}
	isUpdate = true;
}

int find_music(int sub_data[8])
{
	int chunkSum = 0, l, h, m, retID;
	for (int i = 0; i < 8; i++)
	{
		chunkSum += sub_data[i] + BASE_NUMBER;
	}
	chunkSum -= (128 * 16);
	int qStart = 0;
	int qEnd = listID - 1;

	if (isUpdate)
	{
		quickSortUtil(qStart, qEnd);
		isUpdate = false;
	}

	l = 0;
	h = listID - 1;
	while (l <= h)
	{
		m = (l + h) / 2;
		if (chunkSum < gSongList[m].node->start)
		{
			h = m - 1;
		}
		else if (chunkSum > gSongList[m].node->start)
		{
			l = m + 1;
		}
		else
		{
			break;
		}
	}
	int songID, posID, count;

	for (int k = m; k < listID; k++)
	{
		songID = gSongList[k].node->songID;
		posID = gSongList[k].node->position;

		for (count = 0; count < 8; count++)
		{
			if ((songData[songID][posID + count] > (sub_data[count] + 128)) || (songData[songID][posID+count]  < (sub_data[count] - 127)))
				break;
		}
		if (count == 8)
		{
			return songID;
		}
	}

	return 0;
}