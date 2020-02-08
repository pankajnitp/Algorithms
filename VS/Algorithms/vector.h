#pragma once

#ifndef __VCTOR_H__
#define __VCTOR_H__
using namespace std;

template <typename T>
class vectorClass {
private:
	T* arr;
	int capacity;
	int current;

public:
	vectorClass()
	{
		arr = new T[1];
		capacity = 1;
		current = 0;
	}

	void push(T data)
	{
		if (current == capacity) {
			T* temp = new T[2 * capacity];

			// copying old array elements to new array 
			for (int i = 0; i < capacity; i++) {
				temp[i] = std::move(arr[i]);
			}

			// deleting previous array 
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}

		// Inserting data 
		arr[current] = std::move(data);
		current++;
	}

	// function to add element at any index 
	void push(T data, int index)
	{
		if (index == capacity)
			push(data);
		else
			arr[index] = std::move(data);
	}

	T* get(int index)
	{
		// if index is within the range 
		if (index < current)
			return &arr[index];
		else 
			return NULL;
	}

	// function to delete last element 
	void pop()
	{
		current--;
	}

	// function to get size of the vector 
	int size()
	{
		return current;
	}

	// function to get capacity of the vector 
	int getcapacity()
	{
		return capacity;
	}
};

#endif /* __VCTOR_H__ */
