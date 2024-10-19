#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << "\n";
        return 1;
    }

    string filename = argv[1];
    int recordCount = stoi(argv[2]);

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return 1;
    }

    employee emp;

    for (int i = 0; i < recordCount; ++i) {
        cout << "Enter employee " << i + 1 << " data (num, name, hours): ";
        cin >> emp.num >> emp.name >> emp.hours;
        outFile.write((char*)&emp, sizeof(emp));
    }

    outFile.close();
    return 0;
}
