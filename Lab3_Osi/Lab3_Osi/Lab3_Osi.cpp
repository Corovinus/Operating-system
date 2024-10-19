#include "Lab3_Osi.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct MarkerData {
    int threadId;
    int* array;
    int arraySize;
    HANDLE startEvent;
    HANDLE pauseEvent;
    HANDLE stopEvent;
    HANDLE continueEvent;
};

HANDLE outputMutex;

DWORD WINAPI MarkerThread(LPVOID param) {
    MarkerData* data = (MarkerData*)param;
    srand(data->threadId);
    while (true) {
        WaitForSingleObject(data->startEvent, INFINITE);
        while (true) {
            int randValue = rand();
            int index = randValue % data->arraySize;

            if (data->array[index] == 0) {
                Sleep(5);
                data->array[index] = data->threadId;
                Sleep(5);
            }
            else {
                int markedCount = 0;
                for (int i = 0; i < data->arraySize; i++) {
                    if (data->array[i] == data->threadId)
                        markedCount++;
                }
                WaitForSingleObject(outputMutex, INFINITE);
                cout << "Поток " << data->threadId << " не смог пометить индекс " << index + 1 << ". Количество помеченных элементов: " << markedCount << "\n";
                ReleaseMutex(outputMutex);

                SetEvent(data->pauseEvent);

                HANDLE events[2] = { data->continueEvent, data->stopEvent };
                DWORD result = WaitForMultipleObjects(2, events, FALSE, INFINITE);

                if (result == WAIT_OBJECT_0 + 1) {
                    for (int i = 0; i < data->arraySize; i++)
                        if (data->array[i] == data->threadId)
                            data->array[i] = 0;
                    return 0;
                }
                else {
                    ResetEvent(data->continueEvent);
                    ResetEvent(data->pauseEvent);

                    break;
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    outputMutex = CreateMutex(NULL, FALSE, NULL);
    int arraySize;
    cout << "Введите размер массива: \n";
    cin >> arraySize;
    int* array = new int[arraySize]();

    int markerCount;
    cout << "Введите количество экземпляров потока marker: \n";
    cin >> markerCount;
    HANDLE* threads = new HANDLE[markerCount];
    MarkerData* markerData = new MarkerData[markerCount];
    HANDLE* pauseEvents = new HANDLE[markerCount];

    vector<int> activeMarkers;

    for (int i = 0; i < markerCount; i++) {
        markerData[i].threadId = i + 1;
        markerData[i].array = array;
        markerData[i].arraySize = arraySize;
        markerData[i].startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        markerData[i].pauseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        markerData[i].stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        markerData[i].continueEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        pauseEvents[i] = markerData[i].pauseEvent;

        threads[i] = CreateThread(NULL, 0, MarkerThread, &markerData[i], 0, NULL);
        activeMarkers.push_back(i + 1);
    }

    for (int i = 0; i < markerCount; i++) {
        SetEvent(markerData[i].startEvent);
    }

    while (!activeMarkers.empty()) {
        HANDLE* currentPauseEvents = new HANDLE[activeMarkers.size()];
        for (int i = 0; i < activeMarkers.size(); i++) {
            currentPauseEvents[i] = pauseEvents[activeMarkers[i] - 1];
        }
        WaitForMultipleObjects(activeMarkers.size(), currentPauseEvents, TRUE, INFINITE);
        delete[] currentPauseEvents;


        WaitForSingleObject(outputMutex, INFINITE);
        cout << "\nМассив: \n";
        for (int i = 0; i < arraySize; i++)
            cout << array[i] << " ";
        cout << "\n";
        ReleaseMutex(outputMutex);

        int threadIdToStop;
        WaitForSingleObject(outputMutex, INFINITE);
        cout << "Введите номер потока marker, чтобы остановить его: ";
        ReleaseMutex(outputMutex);
        cin >> threadIdToStop;
        cout << "\n";

        auto it = find(activeMarkers.begin(), activeMarkers.end(), threadIdToStop);

        if (it != activeMarkers.end()) {
            SetEvent(markerData[threadIdToStop - 1].stopEvent);
            WaitForSingleObject(threads[threadIdToStop - 1], INFINITE);

            activeMarkers.erase(it);

            WaitForSingleObject(outputMutex, INFINITE);
            cout << "Массив после остановки потока " << threadIdToStop << ": ";
            for (int i = 0; i < arraySize; i++)
                cout << array[i] << " ";
            cout << "\n\n";
            ReleaseMutex(outputMutex);

            ResetEvent(markerData[threadIdToStop - 1].pauseEvent);
            for (int id : activeMarkers) {
                SetEvent(markerData[id - 1].continueEvent);
                ResetEvent(markerData[id - 1].pauseEvent);
            }
        }
        else {
            WaitForSingleObject(outputMutex, INFINITE);
            cout << "Поток с номером " << threadIdToStop << " не активен.\n\nДоступные потоки: ";
            for (int id : activeMarkers) {
                cout << id << " ";
            }
            cout << "\n";
            ReleaseMutex(outputMutex);
        }
    }

    for (int i = 0; i < markerCount; i++) {
        CloseHandle(threads[i]);
        CloseHandle(markerData[i].startEvent);
        CloseHandle(markerData[i].stopEvent);
        CloseHandle(markerData[i].continueEvent);
    }
    CloseHandle(outputMutex);

    delete[] array;
    delete[] threads;
    delete[] markerData;
    delete[] pauseEvents;

    return 0;
}
