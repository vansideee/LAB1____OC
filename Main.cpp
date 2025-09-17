#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "employee.h"

void displayBinaryFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    employee emp;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << emp.num << " " << emp.name << " " << emp.hours << std::endl;
    }
    file.close();
}

void displayTextFile(const char* filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

int main() {
    char binaryFile[100];
    int count;
    std::cout << "Enter binary filename: ";
    std::cin >> binaryFile;
    std::cout << "Enter number of employees: ";
    std::cin >> count;

    // Запуск Creator
    STARTUPINFOA siCreator;
    PROCESS_INFORMATION piCreator;
    ZeroMemory(&siCreator, sizeof(siCreator));
    siCreator.cb = sizeof(siCreator);
    ZeroMemory(&piCreator, sizeof(piCreator));

    char cmdCreator[200];
    sprintf_s(cmdCreator, "Creator.exe %s %d", binaryFile, count);

    if (!CreateProcessA(nullptr, cmdCreator, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &siCreator, &piCreator)) {
        std::cerr << "CreateProcess failed for Creator. Error: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(piCreator.hProcess, INFINITE);
    CloseHandle(piCreator.hProcess);
    CloseHandle(piCreator.hThread);

    std::cout << "Binary file content:\n";
    displayBinaryFile(binaryFile);

    char reportFile[100];
    double payPerHour;
    std::cout << "Enter report filename: ";
    std::cin >> reportFile;
    std::cout << "Enter pay per hour: ";
    std::cin >> payPerHour;

    // Запуск Reporter
    STARTUPINFOA siReporter;
    PROCESS_INFORMATION piReporter;
    ZeroMemory(&siReporter, sizeof(siReporter));
    siReporter.cb = sizeof(siReporter);
    ZeroMemory(&piReporter, sizeof(piReporter));

    char cmdReporter[200];
    sprintf_s(cmdReporter, "Reporter.exe %s %s %.2lf", binaryFile, reportFile, payPerHour);

    if (!CreateProcessA(nullptr, cmdReporter, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &siReporter, &piReporter)) {
        std::cerr << "CreateProcess failed for Reporter. Error: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hProcess);
    CloseHandle(piReporter.hThread);

    std::cout << "Report content:\n";
    displayTextFile(reportFile);

    return 0;
}