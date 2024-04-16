#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <type_traits>
#include <stdlib.h> 
#include <time.h>
#include <stdexcept>

#include "QuickSort.h"

using namespace std;

template <typename T>
QuickSort<T>::QuickSort() {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");
}

template <typename T>
T* QuickSort<T>::sorted(T* data, int size, int left, int right, pivotIndex index) {

	// skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
	T* initial_data = new T[size];

	for (int i = 0; i < size; i++)
		initial_data[i] = data[i];

	this->sort(initial_data, left, right, index);


	return initial_data;
}

template <typename T>
void QuickSort<T>::sort(T* data, int left, int right, pivotIndex index) {


	if (left < right) {
		int s = partition(data, left, right, index);
		this->sort(data, left, s, index);
		this->sort(data, s + 1, right, index);
	}


}

template <typename T>
int QuickSort<T>::partition(T* data, int left, int right, pivotIndex index)
{
	int pivot = data[left];
	srand(time(NULL));

	if (index == LAST)
		pivot = data[right];
	else if (index == MIDDLE)
		pivot = data[(int)((left + right) / 2)];
	else if (index == RANDOM)
		pivot = data[left + (rand() % (right - left + 1))];




	int l = left; int r = right;
	while (1) {
		while (data[l] < pivot)   ++l;
		while (data[r] > pivot)  --r;
		if (l < r) {
			T temp = data[l];
			data[l] = data[r];
			data[r] = temp;
			++l;
			--r;
		}
		else {
			if (r == right) r--;
			return r;
		}
	}
}

template <typename T>
void QuickSort<T>::swap(T* first, T* second) {
	T temp = *first;
	*first = *second;
	*second = temp;
}





template <typename T>
void QuickSort<T>::measure_sorting(int no_times, int size, pivotIndex index) {

	double avg_duration = 0;

	// tyle razy ile zadano, sortuj i zmierz czas
	for (int _ = 0; _ < no_times; _++) {
		T* ptr = this->generate_random_array(size);
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		this->sort(ptr, 0, size - 1, index);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

		double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
		cout << "sorting took: " << sort_duration << "s" << endl;
		avg_duration += sort_duration;
	}

	cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}

template <typename T>
void QuickSort<T>::measure_sorting(int no_times, T* data, int size, pivotIndex index) {


	double avg_duration = 0;

	// tyle razy ile zadano, sortuj i zmierz czas
	for (int _ = 0; _ < no_times; _++) {

		// skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
		T* initial_data = new T[size];

		for (int i = 0; i < size; i++)
			initial_data[i] = data[i];

		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		this->sort(initial_data, 0, size - 1, index);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

		if (!this->is_sorted(initial_data, size, true))
			cout << "NOT SORTED!" << endl;

		double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
		cout << "sorting took: " << sort_duration << "s" << endl;
		avg_duration += sort_duration;
	}

	cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}





template class QuickSort<int>;
template class QuickSort<float>;
template class QuickSort<char>;