#include <iostream>

#include<stdio.h>
#include<time.h>

using namespace std;

#define MIN_MUSIC_LEN 8
#define MAX_MUSIC_NUM 10000
#define MAX_MUSIC_LEN 200
#define MAX_QUERY_NUM 10000
#define SUB_MUSIC_LEN 8

#define mymax(x,y) ((x)>(y)?(x):(y))
#define mymin(x,y) ((x)<(y)?(x):(y))

int score;
int seed = 2010147163;

extern void init(int n);
extern void send_music(int music_id, int music_len, int data1[]);
extern int find_music(int sub_data[8]);

int pseudo_rand()
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

int data1[MAX_MUSIC_NUM + 1][MAX_MUSIC_LEN];
int sub_data[SUB_MUSIC_LEN];
int run(int num_of_music, int len_of_music, int num_of_query)
{
	num_of_music = mymin(num_of_music, MAX_MUSIC_NUM);

	len_of_music = mymax(len_of_music, MIN_MUSIC_LEN);
	len_of_music = mymin(len_of_music, MAX_MUSIC_LEN);

	num_of_query = mymin(num_of_query, MAX_QUERY_NUM);

	init(num_of_music);
	for (register int music_id = 1; music_id <= num_of_music; music_id++)
	{
		for (register int i = 0; i < len_of_music; i++)
		{
			data1[music_id][i] = (pseudo_rand() % 32768) - 16384;
		}
		send_music(music_id, len_of_music, data1[music_id]);
	}

	for (int q = 0; q < num_of_query; q++)
	{
		int music_id = (pseudo_rand() % num_of_music) + 1;
		int start_idx = pseudo_rand() % (len_of_music - 7);
		for (register int i = 0; i < 8; i++)
		{
			register int noise = (pseudo_rand() % 256) - 128;

			sub_data[i] = data1[music_id][start_idx + i] + noise;
			sub_data[i] = mymax(-16384, sub_data[i]);
			sub_data[i] = mymin(16383, sub_data[i]);
		}
		int ans = find_music(sub_data);
		if (ans != music_id)
			return 0;
	}
	return 10;
}

int main()
{
	freopen("music_milan.txt", "r", stdin);
	int T, music_num, music_len, query_num;
	score = 0;
	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; testcase++)
	{
		scanf("%d %d %d", &music_num, &music_len, &query_num);
		score += run(music_num, music_len, query_num);
	}
	if (score >= T * 10)
		printf("PASS\n");
	else
		printf("FAIL\n");
	printf("SCORE : %d\n", score);

	return 0;
}