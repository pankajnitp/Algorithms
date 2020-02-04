#define BASE_NUMBER 16384
#define NULL 0

struct _songChunk {
	short songID;
	short position;
};

_songChunk songChunkPool[200 * 10001];
_songChunk* gSongList[512][15000];
short songData[10005][205];
short length[512];

struct _debugdetails
{
	short hash, idx;
} debugDetails[10001][200];

int poolID, listID;
bool isUpdate;

void init(int n)
{
	poolID = listID = 0;
	isUpdate = false;
	for (int i = 0; i < 512; i++)
		length[i] = 0;
}


void send_music(int music_id, int music_len, int mdata[])
{
	int chunkSum = 0;
	int idx;

	for (int i = 0; i < 8; i++)
	{
		chunkSum += mdata[i] + BASE_NUMBER;
		songData[music_id][i] = mdata[i];
	}

	songChunkPool[poolID].songID = music_id;
	songChunkPool[poolID].position = 0;

	idx = chunkSum / 512;
	gSongList[idx][length[idx]] = &songChunkPool[poolID];
	debugDetails[music_id][0].hash = idx;
	debugDetails[music_id][0].idx = length[idx];

	poolID++;
	length[idx]++;


	for (register int i = 8; i < music_len; i++)
	{
		chunkSum -= (mdata[i-8]);
		chunkSum += (mdata[i]);

		songChunkPool[poolID].songID = music_id;
		songChunkPool[poolID].position = i-7;
		songData[music_id][i] = mdata[i];
		
		idx = chunkSum / 512;
		gSongList[idx][length[idx]] = &songChunkPool[poolID];
		debugDetails[music_id][i-7].hash = idx;
		debugDetails[music_id][i-7].idx = length[idx];

		poolID++;
		length[idx]++;
	}
}

int find_music(int sub_data[8])
{
	int chunkSum = 0, l, h, m, retID, idx;
	for (int i = 0; i < 8; i++)
	{
		chunkSum += sub_data[i] + BASE_NUMBER;
	}
	int songID, posID, count;

	idx = chunkSum / 512;
	for (int i = idx - 2; i <= (idx + 2); i++)
	{
		for (register int k = 0; k < length[i]; k++)
		{
			songID = gSongList[i][k]->songID;
			posID = gSongList[i][k]->position;

			for (count = 0; count < 8; count++)
			{
				if ((songData[songID][posID + count] > (sub_data[count] + 128)) || (songData[songID][posID + count] < (sub_data[count] - 127)))
					break;
			}
			if (count == 8)
			{
				return songID;
			}
		}
	}

	return 0;
}