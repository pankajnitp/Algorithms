#pragma once
#ifndef __HEAP_DEF_H__
#define __HEAP_DEF_H__

#include <vector>

template <typename T>
class heap
{
private:
	vector<T> m_data;
	bool m_ismin;
	int m_num;
	static int left(int i) { return 2 * i ; }
	static int right(int i) { return 2 * i + 1; }
	static int parent(int i) { return i / 2; }
	static bool greater(const T& t1, const T& t2)
	{
		if (m_ismin)
		{
			return t1 < t2;
		}
		else
			return t1 > t2;
	}
	void heapify_up(int i)
	{
		for (int j = parent(i); j >= 0 && greater(m_data[j], m_data[i]); i = j, j = parent(i))
			swap(m_data[i], m_data[j]);
	}
	void heapify_down()
	{

	}
public:
	heap(bool ismin=true) : m_ismin(ismin), m_num(0)
	{
	}
	heap(const vector <T>& d, bool ismin = true) : m_data(d), m_ismin(ismin), m_num(0)
	{

	}
	void push_heap(const T& t)
	{
		m_num++;
		m_data.push_back(t);
		heapify_up(m_num);
	}
	heap& pop_heap()
	{
		swap(m_data[0], m_data[m_num--]);
		heapify_down(0);
		return *this;
	}
	T& get_top()
	{
		return &m_data[0];
	}
	static void make_heap(T& t)
	{

	}
};
#endif // !__HEAP_DEF_H__
