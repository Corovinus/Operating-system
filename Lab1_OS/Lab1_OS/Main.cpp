#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

void runProcess(const string& program, const string& params) {
    STARTUPINFOA si = {  };
    PROCESS_INFORMATION pi;

    string cmdLine = program + " " + params;

    if (CreateProcessA(NULL, &cmdLine[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        cerr << "Failed to start process: " << program << "\nError: " << GetLastError() << endl;
    }
}

int main() {
    string binaryFile, reportFile;
    int recordCount;
    double payPerHour;

    cout << "Enter binary file name: ";
    cin >> binaryFile;
    binaryFile += ".bin";
    cout << "Enter number of emloyeers: ";
    cin >> recordCount;

    runProcess("Creator.exe", binaryFile + " " + to_string(recordCount));

    cout << "Enter report file name: ";
    cin >> reportFile;
    reportFile += ".txt";
    cout << "Enter pay per hour: ";
    cin >> payPerHour;

    runProcess("Reporter.exe", binaryFile + " " + reportFile + " " + to_string(payPerHour));

    return 0;
}
