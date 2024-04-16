#pragma once
#include "Sort.h"


template <typename T>
class HeapSort : public Sort<T> {
public:

	HeapSort();
	void sort(T* data, int size);
	T* sorted(T* data, int size);
	void measure_sorting(int no_times, T* data, int size);
	void measure_sorting(int no_times, int size);

private:
	void heapify(T* data, int size, int i);
};
