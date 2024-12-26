#include "Lab2_1_OS.h"
#include "Windows.h"
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int n;
    cout << "Введите размерность массива:\n";
    cin >> n;

    vector<int> array(n);
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    ThreadParams params{ array, 0, 0, 0.0 };

    thread tMinMax(Min_max, ref(params));
    thread tAverage(Average, ref(params));

    tMinMax.join();
    tAverage.join();

    for (int& value : array) {
        if (value == params.minValue || value == params.maxValue) {
            value = static_cast<int>(params.averageValue);
        }
    }

    cout << "Изменённый массив: ";
    for (const int& value : array) {
        cout << value << " ";
    }
    cout << endl;

    cout << "\nНажмите Enter, чтобы закрыть программу...\n";
    cin.get();
    cin.get();
    return 0;
}
