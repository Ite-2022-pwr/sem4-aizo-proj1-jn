#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <type_traits>
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include <stdexcept>

#include "ShellSort.h"
using namespace std;

template <typename T>
ShellSort<T>::ShellSort() {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");
}

template <typename T>
T* ShellSort<T>::sorted(T* data, int size, gap givenGap) {

	// skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
	T* initial_data = new T[size];

	for (int i = 0; i < size; i++)
		initial_data[i] = data[i];

	this->sort(initial_data, size, givenGap);


	return initial_data;
}

template <typename T>
void ShellSort<T>::sort(T* data, int size, gap givenGap) {

  
    if (givenGap == gap::SHELL) {
        // oryginalne zmniejszane odleg³oœci zaproponowane przez Shella
        for (int gap = size / 2; gap > 0; gap /= 2)
        {

            for (int i = gap; i < size; i += 1)
            {
                int temp = data[i];

                // zmodyfikowany o odleg³oœæ insertion sort
                int j;
                for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                    data[j] = data[j - gap];

                data[j] = temp;
            }
        }
    }
    else {
        // zmniejszanie odleg³oœci zaproponowane przez Franka Lazarusa
        int x = 1;
        int gap = 2 * size / pow(2, x) + 1;
        while(gap > 1)
        {

            for (int i = gap; i < size; i += 1)
            {
                int temp = data[i];

                // zmodyfikowany o odleg³oœæ insertion sort
                int j;
                for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                    data[j] = data[j - gap];

                data[j] = temp;
            }
            gap = 2 * size / pow(2, ++x) + 1;
        }

        // ostatnie insertionSort dla gap = 1
        for (int i = 1; i < size; i += 1)
        {
            int temp = data[i];

            // zmodyfikowany o odleg³oœæ insertion sort
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                data[j] = data[j - gap];

            data[j] = temp;
        }
    }

    

}

template <typename T>
void ShellSort<T>::measure_sorting(int no_times, int size, gap givenGap) {

    double avg_duration = 0;

    // tyle razy ile zadano, sortuj i zmierz czas
    for (int _ = 0; _ < no_times; _++) {
        T* ptr = this->generate_random_array(size);
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        this->sort(ptr, size, givenGap);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
        cout << "sorting took: " << sort_duration << "s" << endl;
        avg_duration += sort_duration;
    }

    cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}

template <typename T>
void ShellSort<T>::measure_sorting(int no_times, T* data, int size, gap givenGap) {


    double avg_duration = 0;

    // tyle razy ile zadano, sortuj i zmierz czas
    for (int _ = 0; _ < no_times; _++) {

        // skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
        T* initial_data = new T[size];

        for (int i = 0; i < size; i++)
            initial_data[i] = data[i];

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        this->sort(initial_data, size, givenGap);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        if (!this->is_sorted(initial_data, size, true))
            cout << "NOT SORTED!" << endl;

        double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
        cout << "sorting took: " << sort_duration << "s" << endl;
        avg_duration += sort_duration;
    }

    cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}





template class ShellSort<int>;
template class ShellSort<float>;
template class ShellSort<char>;