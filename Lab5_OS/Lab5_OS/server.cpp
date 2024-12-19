#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

string pipeName = "\\\\.\\pipe\\EmployeePipe";
string fileName = "employees.dat";

employee findEmployeeById(int id) {
    ifstream inFile(fileName, ios::binary);
    employee e;
    while (inFile.read((char*)&e, sizeof(employee))) {
        if (e.num == id) {
            inFile.close();
            return e;
        }
    }
    inFile.close();
    throw runtime_error("Employee not found.");
}

void updateEmployee(const employee& newEmp) {
    fstream file(fileName, ios::in | ios::out | ios::binary);
    employee e;
    while (file.read((char*)&e, sizeof(employee))) {
        if (e.num == newEmp.num) {
            file.seekp(-static_cast<int>(sizeof(employee)), ios::cur);
            file.write((char*)&newEmp, sizeof(employee));
            file.close();
            return;
        }
    }
    file.close();
    throw runtime_error("Employee not found.");
}

void handleClient(HANDLE pipe) {
    DWORD bytesRead, bytesWritten;
    int command;

    while (true) {
        if (!ReadFile(pipe, &command, sizeof(command), &bytesRead, NULL)) break;

        if (command == 1) {
            int id;
            ReadFile(pipe, &id, sizeof(id), &bytesRead, NULL);
            try {
                employee e = findEmployeeById(id);
                WriteFile(pipe, &e, sizeof(e), &bytesWritten, NULL);
            }
            catch (const exception& ex) {
                employee empty = { -1, "", 0.0 };
                WriteFile(pipe, &empty, sizeof(empty), &bytesWritten, NULL);
            }
        }
        else if (command == 2) {
            employee newEmp;
            ReadFile(pipe, &newEmp, sizeof(newEmp), &bytesRead, NULL);
            updateEmployee(newEmp);
        }
        else if (command == 0) {
            break;
        }
    }
    DisconnectNamedPipe(pipe);
    CloseHandle(pipe);
}

DWORD WINAPI clientHandler(LPVOID param) {
    HANDLE pipe = *(HANDLE*)param;
    handleClient(pipe);
    delete (HANDLE*)param;
    return 0;
}

void createFile() {
    int n;
    cout << "Enter the number of employees: ";
    cin >> n;

    ofstream outFile(fileName, ios::binary);
    for (int i = 1; i <= n; ++i) {
        employee e;
        cout << "Name, and Hours for employee " << i << ": ";
        cin >> e.name >> e.hours;
        e.num = i;
        outFile.write((char*)&e, sizeof(employee));
    }
    outFile.close();
}

void printFile() {
    ifstream inFile(fileName, ios::binary);
    employee e;
    while (inFile.read((char*)&e, sizeof(employee))) {
        cout << "ID: " << e.num << "\t Name: " << e.name << " " << e.hours << endl;
    }
    inFile.close();
}

void startServer(int numThreads) {
    vector<HANDLE> threads(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        HANDLE pipe = CreateNamedPipeA(
            pipeName.c_str(),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            512, 512, 0, NULL);

        if (pipe == INVALID_HANDLE_VALUE) {
            cerr << "Failed to create named pipe." << endl;
            return;
        }

        cout << "Waiting for a client to connect...\n";
        if (ConnectNamedPipe(pipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
            cout << "Client connected.\n";
            HANDLE* param = new HANDLE(pipe);
            threads[i] = CreateThread(
                NULL,
                0,
                clientHandler,
                param,
                0,
                NULL
            );

            if (threads[i] == NULL) {
                cerr << "Failed to create thread for client." << endl;
                delete param;
                CloseHandle(pipe);
            }
        }
        else {
            CloseHandle(pipe);
        }
    }

    for (HANDLE thread : threads) {
        if (thread) {
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
        }
    }
}

void startClients(int numClients) {
    for (int i = 0; i < numClients; ++i) {
        string command = "client.exe";
        STARTUPINFOA si = { sizeof(STARTUPINFOA) };
        PROCESS_INFORMATION pi;

        if (!CreateProcessA(
            NULL,
            command.data(),
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si,
            &pi)) {
            cerr << "Failed to create client process." << endl;
        }
        else {
            cout << "Client process " << i + 1 << " started." << endl;
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }
}

int main() {
    createFile();
    printFile();

    int numClients;
    cout << "Enter the number of clients to start: ";
    cin >> numClients;

    startClients(numClients);
    startServer(numClients);

    printFile();
    return 0;
}
