#pragma once

constexpr int MATH_TC = 0;
constexpr int SHARED_PTR_TC = 0;
constexpr int VECTOR_TC = 0;
constexpr int HEAP_TC = 0;
constexpr int THREADS_EXCLUSION_TC = 1;

#define RUN(func, flag) \
			if(flag) \
				func();