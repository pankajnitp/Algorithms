#define BASE_NUMBER 1024
#define BASE_TABLE 128
#define MAX_ITEM_PER_START 45
#define NULL 0
//#define _DEBUG_

struct _songChunk {
	short songID;
	short position;
};

_songChunk songChunkPool[200 * 10001];
_songChunk* gSongList[2048][256 * MAX_ITEM_PER_START];
short songData[10005][205];
short length[2048][256];

#ifdef _DEBUG_
struct _debugdetails
{
	short hash, idx;
} debugDetails[10001][200];
#endif

int poolID, listID;
bool isUpdate;

void init(int n)
{
	poolID = listID = 0;
	isUpdate = false;
	for (int i = 0; i < 2048; i++)
		for(int j=0; j<256;j++)
			length[i][j] = 0;
}


void send_music(int music_id, int music_len, int mdata[])
{
	int chunkSum = 0;
	int idx, inter_idx, len;

	for (int i = 0; i < 8; i++)
	{
		chunkSum += (mdata[i]/128);
		songData[music_id][i] = mdata[i];
	}

	songChunkPool[poolID].songID = music_id;
	songChunkPool[poolID].position = 0;

	idx = chunkSum + BASE_NUMBER;
	inter_idx = (mdata[0] / 128) + BASE_TABLE;

	gSongList[idx][inter_idx*MAX_ITEM_PER_START + length[idx][inter_idx]] = &songChunkPool[poolID];
#ifdef _DEBUG_
	debugDetails[music_id][0].hash = idx;
	debugDetails[music_id][0].idx = inter_idx*MAX_ITEM_PER_START;
#endif
	poolID++;
	length[idx][inter_idx]++;


	for (register int i = 8; i < music_len; i++)
	{
		chunkSum -= (mdata[i-8])/128;
		chunkSum += (mdata[i])/128;

		songChunkPool[poolID].songID = music_id;
		songChunkPool[poolID].position = i-7;
		songData[music_id][i] = mdata[i];
		
		idx = chunkSum + BASE_NUMBER;
		inter_idx = (mdata[i - 7] / 128) + BASE_TABLE;
		gSongList[idx][inter_idx*MAX_ITEM_PER_START + length[idx][inter_idx]] = &songChunkPool[poolID];
#ifdef _DEBUG_
		debugDetails[music_id][i-7].hash = idx;
		debugDetails[music_id][i-7].idx = inter_idx*MAX_ITEM_PER_START;
#endif
		poolID++;
		length[idx][inter_idx]++;
	}
}

int find_music(int sub_data[8])
{
	int chunkSum = 0, l, h, m, retID, idx, inter_idx;
	int start, end;

	for (int i = 0; i < 8; i++)
	{
		chunkSum += (sub_data[i]/128);
	}
	int songID, posID, count;

	idx = chunkSum + BASE_NUMBER;

	for (int j = -1; j <= 1; j++)
	{
		inter_idx = (sub_data[0] / 128) + j + BASE_TABLE;
		for (int i = idx - 7; i <= (idx + 7); i++)
		{
			start = inter_idx*MAX_ITEM_PER_START;
			end = start + length[i][inter_idx];
			for (register int k = start; k < end; k++)
			{
				songID = gSongList[i][k]->songID;
				posID = gSongList[i][k]->position;

				for (count = 1; count < 8; count++)
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
	}

	return 0;
}