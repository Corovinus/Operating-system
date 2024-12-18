#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    HANDLE hSyncMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"SyncMutex");
    HANDLE hIsFullSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"FullSemaphore");
    HANDLE hIsEmptySem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"EmptySemaphore");
    if (hSyncMutex == NULL) {
        cout << "Error opening mutex named Sync";
        return GetLastError();
    }
    if (hIsFullSem == 0) {
        cout << "Error opening semaphore named IsFull";
        return GetLastError();
    }
    if (hIsEmptySem == 0) {
        cout << "Error opening semaphore named IsEmpty";
        return GetLastError();
    }
    

    WaitForSingleObject(hSyncMutex, INFINITE);
    ReleaseMutex(hSyncMutex);
    string action;
    while (true) {
        cout << "Type message or \"exit\":" << endl;
        cin >> action;
        
        if (action == "exit") break;
        else {
            WaitForSingleObject(hIsEmptySem, INFINITE);
            WaitForSingleObject(hSyncMutex, INFINITE);
            ofstream out(argv[1], ios::app, ios::binary);
            out.write(action.data(), 20);
            out.close();
            ReleaseMutex(hSyncMutex);
            ReleaseSemaphore(hIsFullSem, 1, NULL);
        }
    }
    return 0;
}