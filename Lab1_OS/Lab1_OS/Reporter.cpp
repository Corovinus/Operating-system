#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << "\n";
        return 1;
    }

    string binaryFile = argv[1];
    string reportFile = argv[2];
    double payPerHour = stod(argv[3]);

    ifstream inFile(binaryFile, ios::binary);
    if (!inFile) {
        cerr << "Error opening binary file.\n";
        return 1;
    }

    ofstream outFile(reportFile);
    if (!outFile) {
        cerr << "Error opening report file.\n";
        return 1;
    }

    outFile << "Отчет по файлу \"" << binaryFile << "\"\n";
    outFile << "Номер сотрудника |    Имя    | Часы | Зарплата\n";

    employee emp;
    while (inFile.read((char*)&emp, sizeof(emp))) {
        double salary = emp.hours * payPerHour;
        outFile << setw(17) << emp.num
            << setw(12) << emp.name
            << setw(7) << emp.hours
            << setw(10) << salary << "\n";
    }

    inFile.close();
    outFile.close();
    return 0;
}
