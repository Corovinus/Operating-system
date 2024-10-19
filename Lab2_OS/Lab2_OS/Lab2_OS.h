#pragma once
#include "Windows.h"
#include <iostream>
struct ThreadParams {
	int* array;
	int size;
	int minValue;
	int maxValue;
	double averageValue;
};

DWORD WINAPI Min_max(LPVOID lpParam);
DWORD WINAPI Average(LPVOID lpParam);
