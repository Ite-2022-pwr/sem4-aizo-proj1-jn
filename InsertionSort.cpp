#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <type_traits>

#include "InsertionSort.h"
#include "Sort.h"
using namespace std;

template <typename T>
InsertionSort<T>::InsertionSort() {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");
}


template <typename T>
T* InsertionSort<T>::sort(T* data, int size) {

	// skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
	T* initial_data = new T[size];

	for (int i = 0; i < size; i++)
		initial_data[i] = data[i];


	int j;
	int current_value;

	// pêtla dla ka¿dego elementu listy
	for (int i = 1; i < size; i++) {

		// ustawienie indeksu j na poprzedni element listy
		j = i - 1;
		current_value = initial_data[i];

		// tak d³ugo jak poprzednie elementy listy przed current_value 
		// s¹ od tego mniejsze, zamieniaj je kolejnoœci¹
		while (j >= 0 && initial_data[j] > current_value) {
			initial_data[j + 1] = initial_data[j];
			j--;
		}
		// wstaw na w³aœciwe miejsce porównywany element
		initial_data[j + 1] = current_value;
	}

	return initial_data;

}


template <typename T>
void InsertionSort<T>::measure_sorting(int no_times, int size) {

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
void InsertionSort<T>::measure_sorting(int no_times, T* data, int size) {


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


template class InsertionSort<int>;
template class InsertionSort<float>;
template class InsertionSort<char>;