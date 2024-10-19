#include "Lab2_OS.h"
#include "Windows.h"
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	HANDLE hMin_max, hAverage;
	DWORD IDMin_max, IDAverage;

	int n;
	cout << "Введите размерность массива:\n";
	cin >> n;

	int* array = new int[n];
	cout << "Введите элементы массива:\n";
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}

	ThreadParams params = { array, n, 0, 0, 0.0 };

	hMin_max = CreateThread(NULL, 0, Min_max, (void*)&params, 0, &IDMin_max);
	if (hMin_max == NULL)
		return GetLastError();
	
	hAverage = CreateThread(NULL, 0, Average, (void*)&params, 0, &IDAverage);
	if (hAverage == NULL)
		return GetLastError();
	WaitForSingleObject(hMin_max, INFINITE);
	WaitForSingleObject(hAverage, INFINITE);


	for (int i = 0; i < n; i++) {
		if (array[i] == params.minValue || array[i] == params.maxValue) {
			array[i] = static_cast<int>(params.averageValue);
		}
	}

	cout << "Изменённый массив: ";
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	delete[] array;


	CloseHandle(hMin_max);
	CloseHandle(hAverage);

	cout << "\nНажмите Enter, чтобы закрыть программу...\n";
	cin.get();
	cin.get();
	return 0;
}
