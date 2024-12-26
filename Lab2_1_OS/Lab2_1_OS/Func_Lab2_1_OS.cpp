#include "Windows.h"
#include "Lab2_1_OS.h"
#include <iostream>
using namespace std;
void Min_max(ThreadParams& params) {
    lock_guard<mutex> lock(params.mtx);
    if (params.array.empty()) return;

    params.minValue = params.array[0];
    params.maxValue = params.array[0];

    for (const int& value : params.array) {
        if (value < params.minValue) {
            params.minValue = value;
        }
        this_thread::sleep_for(chrono::milliseconds(7));
        if (value > params.maxValue) {
            params.maxValue = value;
        }
        this_thread::sleep_for(chrono::milliseconds(7));
    }

    cout << "Минимальное значение: " << params.minValue << endl;
    cout << "Максимальное значение: " << params.maxValue << endl;
}

void Average(ThreadParams& params) {
    lock_guard<mutex> lock(params.mtx);
    if (params.array.empty()) return;

    int sum = 0;
    for (const int& value : params.array) {
        sum += value;
        this_thread::sleep_for(chrono::milliseconds(12));
    }

    params.averageValue = static_cast<double>(sum) / params.array.size();
    cout << "Среднее значение: " << params.averageValue << endl;
}
