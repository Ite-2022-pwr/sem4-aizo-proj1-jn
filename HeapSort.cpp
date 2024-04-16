#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <type_traits>
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include <stdexcept>

#include "HeapSort.h"
using namespace std;

template <typename T>
HeapSort<T>::HeapSort() {
    static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
        "Invalid type. Only char, int, and float are allowed.");
}

template <typename T>
void HeapSort<T>::heapify(T* data, int size, int i) {

    int largest = i;

    // indeks lewego i prawego dziecka
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // je¿eli lewe dziecko jest wiêksze od rodzica, zamieñ max wartoœæ
    if (left < size && data[left] > data[largest])
        largest = left;

    // je¿eli prawe dziecko jest wiêksze od rodzica, zamieñ max wartoœæ
    if (right < size && data[right] > data[largest])
        largest = right;

    // je¿eli korzeñ nie jest najwiêkszy, zamieniamy go i znowu wywo³ujemy funkcjê
    if (largest != i) {
        T temp = data[i];
        data[i] = data[largest];
        data[largest] = temp; // Poprawka: zamieñ wartoœæ data[largest] z temp, a nie data[i] z data[largest]

        this->heapify(data, size, largest);
    }

}



template <typename T>
T* HeapSort<T>::sorted(T* data, int size) {

    // skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
    T* initial_data = new T[size];

    for (int i = 0; i < size; i++)
        initial_data[i] = data[i];

    this->sort(initial_data, size);
   

    return initial_data;
}


template <typename T>
void HeapSort<T>::sort(T* data, int size) {

    for (int i = 0; i < size; i++)
        data[i] = data[i];

    // przygotuj kopiec z podanej tablicy
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(data, size, i);

    // wyci¹gaj wartoœci z maksymalnego korzenia 
    for (int i = size - 1; i > 0; i--) {

        // przemieœæ korzeñ (wartoœæ max) na koniec kopca
        T temp = data[0];
        data[0] = data[i];
        data[i] = temp;

        // otwórz kopiec
        heapify(data, i, 0);
    }

}


template <typename T>
void HeapSort<T>::measure_sorting(int no_times, int size) {

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
void HeapSort<T>::measure_sorting(int no_times, T* data, int size) {


    double avg_duration = 0;

    

    // tyle razy ile zadano, sortuj i zmierz czas
    for (int _ = 0; _ < no_times; _++) {

        // skopiuj pocz¹tkowe wartoœci z rozwa¿anej tablicy
        T* initial_data = new T[size];

        for (int i = 0; i < size; i++)
            initial_data[i] = data[i];

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        this->sort(initial_data, size);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        if (!this->is_sorted(initial_data, size, true))
            cout << "NOT SORTED!" << endl;

        double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
        cout << "sorting took: " << sort_duration << "s" << endl;
        avg_duration += sort_duration;
    }

    cout << "average sorting time: " << avg_duration / no_times << "s" << endl;
}




template class HeapSort<int>;
template class HeapSort<float>;
template class HeapSort<char>;