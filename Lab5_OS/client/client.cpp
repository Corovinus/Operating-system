#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

string pipeName = "\\\\.\\pipe\\EmployeePipe";

int main() {
    HANDLE pipe = CreateFileA(
        pipeName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE) {
        cerr << "Failed to connect to the server.\n";
        return 1;
    }

    while (true) {
        int command;
        cout << "Enter command (1: Read, 2: Modify, 0: Exit): ";
        cin >> command;

        DWORD bytesWritten, bytesRead;
        WriteFile(pipe, &command, sizeof(command), &bytesWritten, NULL);

        if (command == 0) break;

        if (command == 1) {
            int id;
            cout << "Enter employee ID to read: ";
            cin >> id;

            string readMutexName = "EmployeeReadMutex_" + to_string(id);
            string editMutexName = "EmployeeEditMutex_" + to_string(id);

            HANDLE readMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, readMutexName.c_str());
            HANDLE editMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, editMutexName.c_str());

            if (!readMutex || !editMutex) {
                if (!readMutex) {
                    readMutex = CreateMutexA(NULL, FALSE, readMutexName.c_str());
                    if (readMutex == NULL) {
                        cerr << "Failed to create read mutex for employee " << id << ".\n";
                        CloseHandle(pipe);
                        return 1;
                    }
                }
                if (!editMutex) {
                    editMutex = CreateMutexA(NULL, FALSE, editMutexName.c_str());
                    if (editMutex == NULL) {
                        cerr << "Failed to create edit mutex for employee " << id << ".\n";
                        CloseHandle(pipe);
                        return 1;
                    }
                }
            }

            DWORD waitResult = WaitForSingleObject(editMutex, 0);
            if (waitResult == WAIT_TIMEOUT) {
                cout << "Employee " << id << " is currently being edited. Reading is not allowed.\n";
                CloseHandle(readMutex);
                CloseHandle(editMutex);
                continue;
            }

            WaitForSingleObject(readMutex, INFINITE);

            employee e;
            WriteFile(pipe, &id, sizeof(id), &bytesWritten, NULL);

            ReadFile(pipe, &e, sizeof(e), &bytesRead, NULL);
            if (e.num != -1) {
                cout << "Employee Details - ID: " << e.num << ", Name: " << e.name
                    << ", Hours: " << e.hours << "\n";
            }
            else {
                cout << "Employee not found.\n";
            }

            ReleaseMutex(readMutex);  
            CloseHandle(readMutex);
            CloseHandle(editMutex);
        }
        else if (command == 2) {  
            int id;
            cout << "Enter employee ID to modify: ";
            cin >> id;

            string readMutexName = "EmployeeReadMutex_" + to_string(id);
            string editMutexName = "EmployeeEditMutex_" + to_string(id);

            HANDLE readMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, readMutexName.c_str());
            HANDLE editMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, editMutexName.c_str());

            if (!readMutex || !editMutex) {
                if (!readMutex) {
                    readMutex = CreateMutexA(NULL, FALSE, readMutexName.c_str());
                    if (readMutex == NULL) {
                        cerr << "Failed to create read mutex for employee " << id << ".\n";
                        CloseHandle(pipe);
                        return 1;
                    }
                }
                if (!editMutex) {
                    editMutex = CreateMutexA(NULL, FALSE, editMutexName.c_str());
                    if (editMutex == NULL) {
                        cerr << "Failed to create edit mutex for employee " << id << ".\n";
                        CloseHandle(pipe);
                        return 1;
                    }
                }
            }

            DWORD waitResult = WaitForSingleObject(editMutex, 1000);
            if (waitResult == WAIT_OBJECT_0) {
                cout << "Trying to access record for modification...\n";

                WaitForSingleObject(readMutex, INFINITE);

                employee e;
                e.num = id;
                cout << "Enter new Name and Hours: ";
                cin >> e.name >> e.hours;

                WriteFile(pipe, &e, sizeof(e), &bytesWritten, NULL);
                cout << "Record updated.\n";

                ReleaseMutex(readMutex);  
                ReleaseMutex(editMutex);  
            }
            else {
                cout << "Record is currently being edited by another client. Please try again later.\n";
            }

            CloseHandle(readMutex);
            CloseHandle(editMutex);
        }
    }

    CloseHandle(pipe);
    return 0;
}
