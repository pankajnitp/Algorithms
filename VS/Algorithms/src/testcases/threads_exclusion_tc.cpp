////// To perform tasks in loop ////

#include <iostream>
#include "testcases.h"
#include <mutex>
#include <thread>
#include <windows.h>

#define TIME_GAP 500

using namespace std;

static mutex mux1;
static mutex mux2;

static int shared_item = 0;

void task1()
{
	while (1)
	{
		while (1)
		{
			mux1.lock();
			if (mux2.try_lock())
			{
				break;
			}
			mux1.unlock();
		}
		cout << "Task1 - shared val = " << shared_item++ << endl;
		Sleep(TIME_GAP);
		mux2.unlock();
		mux1.unlock();
	}
}

void task2()
{
	cout << "Task2 - shared val = " << shared_item++ << endl;
}

void threads_exclusion_tc_main()
{
	thread t1(task1);

	while (1)
	{
		mux2.lock();
		mux1.lock();

		task2();
		Sleep(TIME_GAP);

		mux1.unlock();
		mux2.unlock();
	}

	t1.join();
}