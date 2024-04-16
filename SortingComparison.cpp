#include <iostream>
#include <string>
#include <cstdlib>
#include "Sort.h"
#include "FileHandler.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "Sort.h"
#include "FileHandler.h"

using namespace std;
string decide_load() {
    cout << "\ndo you want to load data from file, or generate random data? <file, random>: ";
    string dataPick;
    cin >> dataPick;

    if (!(dataPick == "file" || dataPick == "random"))
        exit(-1);

    return dataPick;
}

int get_size() {
    cout << "\nchoose size of random generated array ";
    int dataPick;
    cin >> dataPick;

    if (dataPick < 0)
        exit(-1);

    return dataPick;
}

string get_path() {
    cout << "\nprovide absolute path for the file: ";
    string dataPick;
    cin >> dataPick;
    return dataPick;
}


void printData(string dataType, void* data, int size) {
    cout << endl;
    if (dataType == "int")
        Sort<int>::print(static_cast<int*>(data), size);
    else if (dataType == "float")
        Sort<float>::print(static_cast<float*>(data), size);
    else if (dataType == "char")
        Sort<char>::print(static_cast<char*>(data), size);
    cout << endl;
}

void loadData(void*& data, int& size, string& dataType, string& lastDataType) {
    cout << "What kind of data you want to analyze <int, float, char>: ";
    cin >> dataType;


    while (dataType != "int" && dataType != "float" && dataType != "char") {
        cout << "Invalid data type. Please choose from 'int', 'float', or 'char'.\n";
        cin >> dataType;
    }
    
    string dataLoad = decide_load();

    if (dataLoad == "random") {
        size = get_size();
        if (dataType == "int")
            data = Sort<int>::generate_random_array(size);
        else if (dataType == "float")
            data = Sort<float>::generate_random_array(size);
        else if (dataType == "char")
            data = Sort<char>::generate_random_array(size);
    }
    else if (dataLoad == "file") {
        string path = get_path();
        if (dataType == "int") {
            pair<int*, int> load = FileHandler<int>::load(path);
            data = load.first;
            size = load.second;
        }
        else if (dataType == "float") {
            pair<float*, int> load = FileHandler<float>::load(path);
            data = load.first;
            size = load.second;
        }
        else if (dataType == "char") {
            pair<char*, int> load = FileHandler<char>::load(path);
            data = load.first;
            size = load.second;
        }
    }

    printData(dataType, data, size);
    lastDataType = dataType;
    
}

void test() {

    int size = 15000000;
    //int* data = Sort<int>::generate_random_array(size);
    int* data = Sort<int>::generate_sorted_array(size, 0.66, true);

    ShellSort<int> s1;
    ShellSort<int>::gap gapL = ShellSort<int>::LAZARUS;
    ShellSort<int>::gap gapS = ShellSort<int>::SHELL;
    s1.measure_sorting(10, data, size, gapL);
}

int main()
{

    void* data = nullptr;
    int size = 0;
    bool exitProgram = false;
    string lastDataType = "";
    string choose = "";
    string dataType = "";

    while (!exitProgram) {
        cout << "\033[2J\033[1;1H";
        cout << "=====================================================================================\n";
        cout << "Measuring sorting algorithms times\n";
        cout << "=====================================================================================\n\n";


        if (lastDataType != "") {
            std::cout << "You have loaded data of type " << lastDataType;
            printData(lastDataType, data, size);
            std::cout << "Do you wish to operate on it? <y,n>: ";
            cin >> choose;
        }

        if (choose != "y" || choose == "") {
            loadData(data, size, dataType, lastDataType);
        }

        cout << "Pick one of the algorithms to measure <insertSort, quickSort, shellSort, heapSort>: ";
        string algorithm;
        cin >> algorithm;
        while (algorithm != "insertSort" && algorithm != "quickSort" && algorithm != "shellSort" && algorithm != "heapSort") {
            cout << "Please provide legal option: ";
            cin >> algorithm;
        }
        
        if (dataType == "int") {
            if (algorithm == "insertSort") {
                InsertionSort<int> sort;
                int* dataSorted = sort.sort(static_cast<int*>(data), size);
                Sort<int>::print(static_cast<int*>(dataSorted), size);
            }
            else if (algorithm == "quickSort") {
                QuickSort<int> sort;
                cout << "Provide option for the pivot strategy <left,right,middle,random>: ";
                string pivotChoose;
                cin >> pivotChoose;
                while (pivotChoose != "left" && pivotChoose != "right" && pivotChoose != "middle" && pivotChoose != "random") {
                    cout << "Please provide legal option: ";
                    cin >> pivotChoose;
                }

                QuickSort<int>::pivotIndex index;

                if (pivotChoose == "left")
                    index = QuickSort<int>::FIRST;
                else if (pivotChoose == "right")
                    index = QuickSort<int>::LAST;
                else if (pivotChoose == "middle")
                    index = QuickSort<int>::MIDDLE;
                else if (pivotChoose == "random")
                    index = QuickSort<int>::RANDOM;

                int* dataSorted = sort.sorted(static_cast<int*>(data), size, 0, size - 1, index);
                Sort<int>::print(static_cast<int*>(dataSorted), size);
            }
            else if (algorithm == "shellSort") {

                cout << "Provide option for the gap strategy <shell, lazarus>: ";
                string gapChoose;
                cin >> gapChoose;
                while (gapChoose != "shell" && gapChoose != "lazarus") {
                    cout << "Please provide legal option: ";
                    cin >> gapChoose;
                }

                ShellSort<int>::gap gapChosen;

                if (gapChoose == "shell")
                    gapChosen = ShellSort<int>::SHELL;
                else if (gapChoose == "lazarus")
                    gapChosen = ShellSort<int>::LAZARUS;

                ShellSort<int> sort;
                int* dataSorted = sort.sorted(static_cast<int*>(data), size, gapChosen);
                Sort<int>::print(static_cast<int*>(dataSorted), size);
            }
            else if (algorithm == "heapSort") {
                HeapSort<int> sort;
                int* dataSorted = sort.sorted(static_cast<int*>(data), size);
                Sort<int>::print(static_cast<int*>(dataSorted), size);
            }
        }

        else if (dataType == "float") {

            float* dataSorted = nullptr;

            if (algorithm == "insertSort") {
                InsertionSort<float> sort;
                dataSorted = sort.sort(static_cast<float*>(data), size);
            }
            else if (algorithm == "quickSort") {
                QuickSort<float> sort;
                cout << "Provide option for the pivot strategy <left,right,middle,random>: ";
                string pivotChoose;
                cin >> pivotChoose;
                while (pivotChoose != "left" && pivotChoose != "right" && pivotChoose != "middle" && pivotChoose != "random") {
                    cout << "Please provide legal option: ";
                    cin >> pivotChoose;
                }

                QuickSort<float>::pivotIndex index;

                if (pivotChoose == "left")
                    index = QuickSort<float>::FIRST;
                else if (pivotChoose == "right")
                    index = QuickSort<float>::LAST;
                else if (pivotChoose == "middle")
                    index = QuickSort<float>::MIDDLE;
                else if (pivotChoose == "random")
                    index = QuickSort<float>::RANDOM;

                dataSorted = sort.sorted(static_cast<float*>(data), size, 0, size - 1, index);
            }
            else if (algorithm == "shellSort") {

                cout << "Provide option for the gap strategy <shell, lazarus>: ";
                string gapChoose;
                cin >> gapChoose;
                while (gapChoose != "shell" && gapChoose != "lazarus") {
                    cout << "Please provide legal option: ";
                    cin >> gapChoose;
                }

                ShellSort<float>::gap gapChosen;

                if (gapChoose == "shell")
                    gapChosen = ShellSort<float>::SHELL;
                else if (gapChoose == "lazarus")
                    gapChosen = ShellSort<float>::LAZARUS;

                ShellSort<float> sort;
                float* dataSorted = sort.sorted(static_cast<float*>(data), size, gapChosen);
                Sort<float>::print(static_cast<float*>(dataSorted), size);
            }
            else if (algorithm == "heapSort") {
                HeapSort<float> sort;
                dataSorted = sort.sorted(static_cast<float*>(data), size);
            }

            Sort<float>::print(static_cast<float*>(dataSorted), size);
        }
        else if (dataType == "char") {

            char* dataSorted = nullptr;
            if (algorithm == "insertSort") {
                InsertionSort<char> sort;
                dataSorted = sort.sort(static_cast<char*>(data), size);
            }
            else if (algorithm == "quickSort") {
                QuickSort<char> sort;
                cout << "Provide option for the pivot strategy <left,right,middle,random>: ";
                string pivotChoose;
                cin >> pivotChoose;
                while (pivotChoose != "left" && pivotChoose != "right" && pivotChoose != "middle" && pivotChoose != "random") {
                    cout << "Please provide legal option: ";
                    cin >> pivotChoose;
                }

                QuickSort<char>::pivotIndex index;

                if (pivotChoose == "left")
                    index = QuickSort<char>::FIRST;
                else if (pivotChoose == "right")
                    index = QuickSort<char>::LAST;
                else if (pivotChoose == "middle")
                    index = QuickSort<char>::MIDDLE;
                else if (pivotChoose == "random")
                    index = QuickSort<char>::RANDOM;

                dataSorted = sort.sorted(static_cast<char*>(data), size, 0, size - 1, index);
            }
            else if (algorithm == "shellSort") {

                cout << "Provide option for the gap strategy <shell, lazarus>: ";
                string gapChoose;
                cin >> gapChoose;
                while (gapChoose != "shell" && gapChoose != "lazarus") {
                    cout << "Please provide legal option: ";
                    cin >> gapChoose;
                }

                ShellSort<char>::gap gapChosen;

                if (gapChoose == "shell")
                    gapChosen = ShellSort<char>::SHELL;
                else if (gapChoose == "lazarus")
                    gapChosen = ShellSort<char>::LAZARUS;

                ShellSort<char> sort;
                char* dataSorted = sort.sorted(static_cast<char*>(data), size, gapChosen);
                Sort<char>::print(static_cast<char*>(dataSorted), size);

            }
            else if (algorithm == "heapSort") {
                HeapSort<char> sort;
                dataSorted = sort.sorted(static_cast<char*>(data), size);
            }

            Sort<char>::print(static_cast<char*>(dataSorted), size);
        }

        cout << "Continue program? <y,n>: ";
        string continueChoose;
        cin >> continueChoose;

        if (continueChoose != "y")
            exitProgram = true;
    }
    return 0;
}
