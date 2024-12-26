// Lab2_1_OS.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <vector>
#include <mutex>
using namespace std;
struct ThreadParams {
    vector<int> array;
    int minValue;
    int maxValue;
    double averageValue;
    mutex mtx; 
};

void Min_max(ThreadParams& params);

void Average(ThreadParams& params);

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
