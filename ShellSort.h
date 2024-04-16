#pragma once
#include "Sort.h"


template <typename T>
class ShellSort : public Sort<T> {
public:

	enum gap {
		SHELL,
		LAZARUS
	};
	
	ShellSort();
	void sort(T* data, int size, gap givenGap);
	T* sorted(T* data, int size, gap givenGap);
	void measure_sorting(int no_times, T* data, int size, gap givenGap);
	void measure_sorting(int no_times, int size, gap givenGap);
};