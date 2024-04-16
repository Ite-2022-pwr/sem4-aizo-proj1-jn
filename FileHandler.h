#pragma once
#include <utility>

using namespace std;

template <typename T>
class FileHandler {
public:
	static pair<T*, int> load(std::string path);
};