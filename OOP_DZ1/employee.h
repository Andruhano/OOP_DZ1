#pragma once

struct Employee {
    char* firstName;
    char* lastName;
    char* phoneNumber;
    double salary;
};

void loadFromFile(Employee*& employees, size_t& size, const char* fileName);
void saveToFile(const Employee* employees, size_t size, const char* fileName);
void displayAllEmployees(const Employee* employees, size_t size);
void searchByLastName(const Employee* employees, size_t size, const char* lastName);
void searchBySalaryRange(const Employee* employees, size_t size, double minSalary, double maxSalary);
void sortByLastName(Employee* employees, size_t size);
void addEmployee(Employee*& employees, size_t& size);
void removeEmployee(Employee*& employees, size_t& size, const char* lastName);