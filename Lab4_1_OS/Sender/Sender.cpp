#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    HANDLE hSyncMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, "Sync");
    HANDLE hIsFullSem = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "IsFull");
    HANDLE hIsEmptySem = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "IsEmpty");
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
        getline(cin, action);

        if (action == "exit") break;

        action += "\n";

        DWORD dwWaitResult = WaitForSingleObject(hIsEmptySem, 0);
        if (dwWaitResult == WAIT_TIMEOUT) {
            cout << "Message limit reached. Cannot add more messages.\n";
            continue;
        }

        WaitForSingleObject(hSyncMutex, INFINITE);

        ofstream out(argv[1], ios::app | ios::binary);
        out.write(action.data(), action.size());
        out.close();

        ReleaseMutex(hSyncMutex);
        ReleaseSemaphore(hIsFullSem, 1, NULL);
    }

    return 0;
}