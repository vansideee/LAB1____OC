#include <iostream>
#include <fstream>
#include <iomanip>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <binary_file> <report_file> <pay_per_hour>" << std::endl;
        return 1;
    }

    const char* binaryFilename = argv[1];
    const char* reportFilename = argv[2];
    double payPerHour = std::atof(argv[3]);

    std::ifstream inFile(binaryFilename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Cannot open binary file!" << std::endl;
        return 1;
    }

    std::ofstream outFile(reportFilename);
    outFile << "Report for file \"" << binaryFilename << "\"\n";
    outFile << "Number\tName\tHours\tSalary\n";

    employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * payPerHour;
        outFile << emp.num << "\t" << emp.name << "\t"
            << std::fixed << std::setprecision(2) << emp.hours << "\t" << salary << "\n";
    }

    inFile.close();
    outFile.close();
    return 0;
}