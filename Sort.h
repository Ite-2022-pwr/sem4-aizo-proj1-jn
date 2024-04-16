#pragma once

template <typename T>
class Sort {

public:
	Sort();
	Sort(T* data, int size);
	static T*  generate_random_array(int size);
	static T* generate_sorted_array(int size, float percentage_sorted, bool asc);
	T* sort(T* data, int size);
	void measure_sorting(int no_times, T* data, int size);
	void measure_sorting(int no_times, int size);
	static void print(T* data, int size);
	bool is_sorted(T* data, int size, bool asc);

protected:
	T* not_sorted_data;
	T* data;
	int size;
};