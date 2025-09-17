#include <iostream>
#include <fstream>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <binary_file> <count>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    int count = std::atoi(argv[2]);

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open file!" << std::endl;
        return 1;
    }

    employee emp;
    for (int i = 0; i < count; ++i) {
        std::cout << "Enter employee number: ";
        std::cin >> emp.num;
        std::cout << "Enter employee name (max 9 chars): ";
        std::cin >> emp.name;
        std::cout << "Enter hours worked: ";
        std::cin >> emp.hours;

        outFile.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    outFile.close();
    return 0;
}