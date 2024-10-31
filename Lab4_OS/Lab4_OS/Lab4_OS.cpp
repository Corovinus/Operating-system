#include "Lab4_OS.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> prosts;
HANDLE hMutex; 

bool isProst(int number) {
    if (number < 2) return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

DWORD WINAPI findProst(LPVOID param) {
    int* range = static_cast<int*>(param);
    int start = range[0];
    int end = range[1];

    for (int i = start; i <= end; ++i) {
        if (isProst(i)) {
            WaitForSingleObject(hMutex, INFINITE);
            prosts.push_back(i);
            ReleaseMutex(hMutex);
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int startRange, endRange, numThreads;

    cout << "Введите начальное значение диапазона: ";
    cin >> startRange;
    cout << "Введите конечное значение диапазона: ";
    cin >> endRange;
    cout << "Введите количество потоков: ";
    cin >> numThreads;

    int rangePerThread = (endRange - startRange + 1) / numThreads;
    HANDLE* threads = new HANDLE[numThreads];
    int** ranges = new int* [numThreads];

    hMutex = CreateMutex(nullptr, FALSE, nullptr);
    if (hMutex == nullptr) {
        cerr << "Ошибка создания мьютекса." << endl;
        return 1;
    }

    for (int i = 0; i < numThreads; ++i) {
        int rangeStart = startRange + i * rangePerThread;
        int rangeEnd = (i == numThreads - 1) ? endRange : rangeStart + rangePerThread - 1;

        ranges[i] = new int[2] { rangeStart, rangeEnd };
        threads[i] = CreateThread(nullptr, 0, findProst, ranges[i], 0, nullptr);
    }

    WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

    for (int i = 0; i < numThreads; ++i) {
        CloseHandle(threads[i]);
        delete[] ranges[i];
    }
    delete[] threads;
    delete[] ranges;

    CloseHandle(hMutex);

    cout << "Найденные простые числа:\n";
    sort(prosts.begin(), prosts.end());
    for (int prost : prosts) {
        cout << prost << " ";
    }
    cout << endl;
    cin.get();
    cin.get();
    return 0;
}
