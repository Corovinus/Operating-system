#include "Windows.h"
#include "Lab2_OS.h"
#include <iostream>
using namespace std;
DWORD WINAPI Min_max(LPVOID lpParam) {
	ThreadParams* params = (ThreadParams*)lpParam;
	params->minValue = params->array[0];
	params->maxValue = params->array[0];

	for (int i = 0; i < params->size; i++) {
		if (params->array[i] < params->minValue) {
			params->minValue = params->array[i];
		}
		Sleep(7);
		if (params->array[i] > params->maxValue) {
			params->maxValue = params->array[i];
		}
		Sleep(7);
	}

	cout << "Минимальное значение: " << params->minValue << endl;
	cout << "Максимальное значение: " << params->maxValue << endl;

	return 0;
}

DWORD WINAPI Average(LPVOID lpParam) {
	ThreadParams* params = (ThreadParams*)lpParam;
	int sum = 0;

	for (int i = 0; i < params->size; i++) {
		sum += params->array[i];
		Sleep(12);
	}

	params->averageValue = static_cast<double>(sum) / params->size;
	cout << "Среднее значение: " << params->averageValue << endl;

	return 0;
}
