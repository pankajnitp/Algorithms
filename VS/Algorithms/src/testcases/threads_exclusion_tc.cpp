////// To perform tasks in loop ////

#include <iostream>
#include "testcases.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <windows.h>

#define TIME_GAP 500

using namespace std;

std::mutex mux;
std::condition_variable cond_var;

static int shared_val = 0;
static bool enable_worker = false;
static bool enable_main = true;

void worker_fn()
{
	while (1)
	{
		std::unique_lock<std::mutex> lck(mux);
		cond_var.wait(lck, [] {return enable_worker; });

		cout << "Worker sees val = " << shared_val++ << endl;
		Sleep(TIME_GAP);

		enable_main = true;
		enable_worker = false;

		cond_var.notify_one();
	}
}

void main_fn()
{
	cout << "Main sees val = " << shared_val++ << endl;
}

void threads_exclusion_tc_main()
{
	// Worker thread
	thread worker(worker_fn);

	//Main thread continues
	main_fn();
	enable_worker = true;
	enable_main = false;
	cond_var.notify_one(); // notify worker thread else it will keep waiting forever

	while (1)
	{
		std::unique_lock<std::mutex> lck(mux);
		cond_var.wait(lck, [] {return enable_main; });

		main_fn();
		Sleep(TIME_GAP);

		enable_main = false;
		enable_worker = true;

		cond_var.notify_one();
	}

	//Main thread waits until worker thread returns
	worker.join();
}