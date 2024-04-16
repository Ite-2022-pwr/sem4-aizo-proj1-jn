#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <type_traits>
#include <chrono>
#include "Sort.h"

using namespace std;

template <typename T>
Sort<T>::Sort() {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");
}


template <typename T>
Sort<T>::Sort(T* data, int size) {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");

	this->data = data;
	this->size = size;

}

template <typename T>
T* Sort<T>::sort(T* data, int size) {
	cout << "sort() method not implemented" << endl;
	return nullptr;
};

template <typename T>
void Sort<T>::measure_sorting(int no_times, int size) {

	double avg_duration = 0;

	// tyle razy ile zadano, sortuj i zmierz czas
	for (int _ = 0; _ < no_times; _++) {
		T* ptr = this->generate_random_array(size);
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		this->sort(ptr, size);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

		double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
		cout << "sorting took: " << sort_duration << "s" << endl;
		avg_duration += sort_duration;
	}

	cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}

template <typename T>
void Sort<T>::measure_sorting(int no_times, T* data, int size) {


	double avg_duration = 0;

	// tyle razy ile zadano, sortuj i zmierz czas
	for (int _ = 0; _ < no_times; _++) {

		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		T* sorted = this->sort(data, size);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

		if (!this->is_sorted(sorted, size, true))
			cout << "NOT SORTED!" << endl;

		double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
		cout << "sorting took: " << sort_duration << "s" << endl;
		avg_duration += sort_duration;
	}

	cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}

template <typename T>
void Sort<T>::print(T* data, int size) {
	for (int i = 0; i < size; i++)
		cout << data[i] << endl;
}


template <typename T>
T* Sort<T>::generate_random_array(int size) {

	// initialize random seed for rand func
	srand(time(NULL));

	// initialize empty array of generated data
	T* data = new T[size];

	// fill array with random number from 1 to 100
	for (int i = 0; i < size; i++) {
		data[i] = (T)(rand() % 100 + 1);
	}

	return data;
}

template <typename T>
T* Sort<T>::generate_sorted_array(int size, float percentage_sorted, bool asc) {

	if (percentage_sorted > 1 || percentage_sorted < 0) {
		cout << "Percentage_sorted should have value in range <0;1> \n";
		return nullptr;
	}

	// initialize random seed for rand func
	srand(time(NULL));

	// initialize empty array of generated data
	T* data = new T[size];

	// fill array with ascending data respecting percentage sorted provided
	float current_percentage;
	for (int i = 0; i < size; i++) {
		float current_percentage = static_cast<float>(i) / size;
		if (current_percentage <= percentage_sorted)
			data[i] = (asc) ? (T)i : (T)(size-i);
		else
			data[i] = (T)(rand() % 100 + 1);
	}

	return data;
}

template <typename T>
bool Sort<T>::is_sorted(T* data, int size, bool asc) {

	// check for order and if two adjancent elements dont 
	// suit with order, return false
	for (int i = 1; i < size; i++) {
		if (
			(asc && data[i - 1] > data[i]) ||
			(!asc && data[i - 1] < data[i])
		)
			return false;
	}

	return true;
}





template class Sort<int>;
template class Sort<float>;
template class Sort<char>;