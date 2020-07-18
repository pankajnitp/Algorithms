#include<iostream>
#include "testcases.h"
#include "tc_controller.h"

using namespace std;

int main()
{
	RUN(math_tc_main, MATH_TC);
	RUN(shared_ptr_tc_main, SHARED_PTR_TC);
	RUN(vector_tc_main, VECTOR_TC);

	RUN(heap_tc_main, HEAP_TC);
	RUN(threads_exclusion_tc_main, THREADS_EXCLUSION_TC);

	return 0;
}
