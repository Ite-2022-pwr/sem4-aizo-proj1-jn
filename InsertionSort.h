#pragma once
#include "Sort.h"


template <typename T>
class InsertionSort: public Sort<T>{
public:
	InsertionSort();
	T* sort(T* data, int size);
	void measure_sorting(int no_times, T* data, int size);
	void measure_sorting(int no_times, int size);
};