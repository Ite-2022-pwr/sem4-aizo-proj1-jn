#pragma once
#include "Sort.h"


template <typename T>
class QuickSort : public Sort<T> {
public:
	enum pivotIndex {
		FIRST,
		LAST,
		MIDDLE,
		RANDOM
	};

	QuickSort();
	T* sorted(T* data, int size, int left, int right, pivotIndex index);
	void sort(T* data, int left, int right, pivotIndex index);
	void measure_sorting(int no_times, T* data, int size, pivotIndex index);
	void measure_sorting(int no_times, int size, pivotIndex index);
	

private:
	int partition(T* data, int left, int right, pivotIndex index);
	void swap(T* first, T* second);
};