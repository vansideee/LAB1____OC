// Core/employee.h
#pragma once

#include <iostream>
#include <fstream>

struct employee {
    int num;
    char name[10];
    double hours;

    // Перегрузка оператора вывода 
    friend std::ostream& operator<<(std::ostream& os, const employee& emp) {
        os.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, employee& emp) {
        is.read(reinterpret_cast<char*>(&emp), sizeof(employee));
        return is;
    }

    
    bool operator==(const employee& other) const {
        return num == other.num && 
               strcmp(name, other.name) == 0 && 
               hours == other.hours;
    }
};