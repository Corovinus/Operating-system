#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
int main() {
    string filename, params;
    int messangesCount, sendersCount;
    cout << "Enter filename:" << endl;
    cin >> filename;
    filename += ".bin";
    cout << "Enter number of messanges:" << endl;

    do {
        cin >> messangesCount;
        if (messangesCount < 1) {
			cout << "incorrect number of messanges" << endl;
		}
    } while (messangesCount < 1);

params = "Sender.exe \"" + filename + "\"";

    ofstream binFile(filename, ios::binary);
    binFile.close();
    
    HANDLE hMutex = CreateMutex(NULL, FALSE, L"SyncMutex");
    HANDLE hFull = CreateSemaphore(NULL, 0, messangesCount, L"FullSemaphore");
    HANDLE hEmpty = CreateSemaphore(NULL, messangesCount, messangesCount, L"EmptySemaphore");

    if (hMutex == NULL) {
        cout << "MUTEX ERROR" << endl;
        return GetLastError();
    }

    WaitForSingleObject(hMutex, INFINITE);
    cout << "Print number of senders: " << endl;
    cin >> sendersCount;
    if (sendersCount < 1) {
        cout << "incorrect number of receivers";
        return 1;
    }
    STARTUPINFOA* si = new STARTUPINFOA[sendersCount];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[sendersCount];
    HANDLE* hProcessors = new HANDLE[sendersCount];
    cout << params << endl;
    ZeroMemory(si, sizeof(STARTUPINFOA)*sendersCount);
    for (int i = 0; i < sendersCount; i++) {
        si[i].cb = sizeof(STARTUPINFOA);

        if (!CreateProcessA(NULL, params.data(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[i], &pi[i])) {
            cout << "Error creating process " << i << ": " << GetLastError() << endl;
            return 1;
        }
        hProcessors[i] = pi[i].hProcess;
    }
    Sleep(100);
    if (sendersCount == 1) 
        WaitForSingleObject(&hProcessors, INFINITE);

    else 
        WaitForMultipleObjects(sendersCount, hProcessors, TRUE, INFINITE);

    ifstream in;
    ofstream out;
    ReleaseMutex(hMutex);
    string action;
    char *fileElem = new char[20];
    string deleting;
    while (true) {
        cout << "Choose operation:\n1.read\n2.exit\n";
        cin >> action;
        
        if (action == "exit" or action == "1") {
            for (int i = 0; i < sendersCount; i++) {
                TerminateProcess(pi[i].hProcess, 1);
                TerminateProcess(pi[i].hThread, 1);
            }
            break;
        }
        else  if (action == "read" or action == "2") {
            WaitForSingleObject(hFull, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);
            in.open(filename, ios::binary);
            in.read(fileElem, 20);
            in >> deleting;
            if (strcmp(fileElem, deleting.data()) == 0)
                deleting = "";
            in.close();
            
            out.open(filename, ios::binary);
            out.clear();
            out.write(deleting.data(), deleting.size());
            out.close();
            cout << fileElem << endl;
            ReleaseMutex(hMutex);
            ReleaseSemaphore(hEmpty, 1, NULL);
        }
        else
        {
            cout << "Incorrect action" << endl;
        }
    }
    
    WaitForMultipleObjects(sendersCount, &pi->hProcess, TRUE, INFINITE);

    for (int i = 0; i < sendersCount; i++) {
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
        
    }
    CloseHandle(hMutex);
    CloseHandle(hFull);
    CloseHandle(hEmpty);
    in.close();
}