#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <utility>
#include "FileHandler.h"

using namespace std;

template <typename T>
pair<T*, int> FileHandler<T>::load(string path) {
	static_assert(std::is_same<T, char>::value || std::is_same<T, int>::value || std::is_same<T, float>::value,
		"Invalid type. Only char, int, and float are allowed.");

	ifstream dataFile(path);

	if (!dataFile.is_open()) {
		throw std::runtime_error("error: File not found.");
	}

	string line;
	int i = 0;
	int size = 0;
	int initSize = 0;
	T* data = nullptr;

	while (getline(dataFile, line)) {
		if (i == 0) {
			size = stoi(line);
			initSize = stoi(line);
			data = (T*)malloc(size * sizeof(T));
			i++;
			continue;
		}

		if (size <= 0)
			break;

		data[i - 1] = static_cast<T>(stoi(line));
		i++;
		size--;
	}

	dataFile.close();

	return make_pair(data, initSize);
}


template std::pair<int*, int> FileHandler<int>::load(std::string);
template std::pair<char*, int> FileHandler<char>::load(std::string);
template std::pair<float*, int> FileHandler<float>::load(std::string);