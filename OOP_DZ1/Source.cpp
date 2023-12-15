#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "employee.h"
using namespace std;

void loadFromFile(Employee*& employees, size_t& size, const char* fileName)
{
    FILE* file = fopen(fileName, "r");

    if (file == nullptr)
    {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    size_t initialSize = 10;
    size = 0;

    employees = new Employee[initialSize];

    char line[256];
    while (fgets(line, sizeof(line), file) != nullptr)
    {
        char firstName[50], lastName[50], phoneNumber[50];
        double salary;
        if (sscanf(line, "%s %s %s %lf", firstName, lastName, phoneNumber, &salary) == 4)
        {

            firstName[sizeof(firstName) - 1] = '\0';
            lastName[sizeof(lastName) - 1] = '\0';
            phoneNumber[sizeof(phoneNumber) - 1] = '\0';

            employees[size].firstName = new char[strlen(firstName) + 1];
            strcpy(employees[size].firstName, firstName);

            employees[size].lastName = new char[strlen(lastName) + 1];
            strcpy(employees[size].lastName, lastName);

            employees[size].phoneNumber = new char[strlen(phoneNumber) + 1];
            strcpy(employees[size].phoneNumber, phoneNumber);

            employees[size].salary = salary;

            size++;

            if (size == initialSize)
            {
                initialSize *= 2;
                Employee* temp = new Employee[initialSize];

                for (size_t i = 0; i < size; i++)
                {
                    temp[i] = employees[i];
                }

                delete[] employees;

                employees = temp;
            }
        }
        else
        {
            cout << "Error reading line: " << line << "\n";
        }
    }

    fclose(file);
}




void saveToFile(const Employee* employees, size_t size, const char* fileName)
{
    FILE* file = fopen(fileName, "w"); 

    if (file == nullptr)
    {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        fprintf(file, "%s %s %s %.2lf\n",
            employees[i].firstName,
            employees[i].lastName,
            employees[i].phoneNumber,
            employees[i].salary);
    }

    fclose(file);
    cout << "Data saved to file successfully.\n";
}

void displayAllEmployees(const Employee* employees, size_t size) 
{
    for (size_t i = 0; i < size; i++) 
    {
        cout << "Employee " << i + 1 << ":\n";
        cout << "First Name: " << employees[i].firstName << "\n";
        cout << "Last Name: " << employees[i].lastName << "\n";
        cout << "Phone Number: " << employees[i].phoneNumber << "\n";
        cout << "Salary: " << employees[i].salary << "\n\n";
    }
}

void searchByLastName(const Employee* employees, size_t size) 
{
    string searchLastName;

    cout << "Enter the last name to search for: ";
    cin >> searchLastName;

    bool found = false;

    for (size_t i = 0; i < size; i++) 
    {

        if (searchLastName == employees[i].lastName) 
        {
            cout << "Employee with last name " << searchLastName << " found:\n";
            cout << "First Name: " << employees[i].firstName << "\n";
            cout << "Last Name: " << employees[i].lastName << "\n";
            cout << "Phone Number: " << employees[i].phoneNumber << "\n";
            cout << "Salary: " << employees[i].salary << "\n\n";
            found = true;
        }
    }

    if (!found) 
    {
        cout << "No employees found with last name " << searchLastName << "\n";
    }
}

void searchBySalaryRange(const Employee* employees, size_t size) 
{
    double minSalary, maxSalary;

    cout << "Enter the minimum salary: ";
    cin >> minSalary;

    cout << "Enter the maximum salary: ";
    cin >> maxSalary;

    bool found = false;

    for (size_t i = 0; i < size; i++) 
    {
        if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary) 
        {
            cout << "Employee with salary in the range " << minSalary << " to " << maxSalary << " found:\n";
            cout << "First Name: " << employees[i].firstName << "\n";
            cout << "Last Name: " << employees[i].lastName << "\n";
            cout << "Phone Number: " << employees[i].phoneNumber << "\n";
            cout << "Salary: " << employees[i].salary << "\n\n";
            found = true;
        }
    }

    if (!found) 
    {
        cout << "No employees found with salary in the range " << minSalary << " to " << maxSalary << "\n";
    }
}

void swap(Employee& a, Employee& b) {
    Employee temp = a;
    a = b;
    b = temp;
}

bool isLess(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }

    return *str1 > *str2;
}

void sortByLastName(Employee* employees, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (isLess(employees[j].lastName, employees[j + 1].lastName)) {
                swap(employees[j], employees[j + 1]);
            }
        }
    }
}

bool isNumeric(const char* str) 
{
    while (*str) 
    {
        if (!isdigit(*str)) 
        {
            return false;
        }
        ++str;
    }
    return true;
}

void addEmployee(Employee*& employees, size_t& size)
{
    Employee newEmployee = {};

    cout << "Enter the first name: ";
    char tempFirstName[50];
    cin >> tempFirstName;
    newEmployee.firstName = new char[strlen(tempFirstName) + 1];
    strcpy(newEmployee.firstName, tempFirstName);

    cout << "Enter the last name: ";
    char tempLastName[50];
    cin >> tempLastName;
    newEmployee.lastName = new char[strlen(tempLastName) + 1];
    strcpy(newEmployee.lastName, tempLastName);

    char tempPhoneNumber[50];
    do
    {
        cout << "Enter the phone number (must start with '+' and have 13 digits): ";
        cin >> tempPhoneNumber;
    } while (tempPhoneNumber[0] != '+' || strlen(tempPhoneNumber) != 13);
    newEmployee.phoneNumber = new char[strlen(tempPhoneNumber) + 1];
    strcpy(newEmployee.phoneNumber, tempPhoneNumber);

    do
    {
        cout << "Enter the salary: ";
        cin >> newEmployee.salary;

        if (cin.fail())
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid input. Please enter a numeric value.\n";
        }
    } while (cin.fail());

    FILE* outFile = fopen("data.txt", "a");  

    if (outFile != nullptr)
    {
        fprintf(outFile, "%s %s %s %.2lf\n",
            newEmployee.firstName,
            newEmployee.lastName,
            newEmployee.phoneNumber,
            newEmployee.salary);

        fclose(outFile);

        size++;
        Employee* tempArray = new Employee[size];

        for (size_t i = 0; i < size - 1; i++)
        {
            tempArray[i] = employees[i];
        }

        tempArray[size - 1] = newEmployee;

        delete[] employees;
        employees = tempArray;

        cout << "Employee added successfully.\n";
    }
    else
    {
        cout << "Error opening file for writing.\n";
    }
}


void removeEmployee(Employee*& employees, size_t& size)
{
    cout << "Enter the last name of the employee to remove: ";
    char lastName[50];
    cin >> lastName;

    bool found = false;

    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(employees[i].lastName, lastName) == 0)
        {
            found = true;

            delete[] employees[i].firstName;
            delete[] employees[i].lastName;
            delete[] employees[i].phoneNumber;

            for (size_t j = i; j < size - 1; ++j)
            {
                employees[j] = employees[j + 1];
            }

            --size;

            Employee* tempArray = new Employee[size];
            for (size_t j = 0; j < size; ++j)
            {
                tempArray[j] = employees[j];
            }

            delete[] employees;

            employees = tempArray;

            cout << "Employee with last name " << lastName << " removed successfully.\n";

            break;  
        }
    }

    if (!found)
    {
        cout << "No employees found with last name " << lastName << ". No changes made.\n";
    }
}

void cleanupMemory(Employee*& employees, size_t& size)
{
    if (employees != nullptr) {
        for (size_t i = 0; i < size; i++)
        {
            delete[] employees[i].firstName;
            delete[] employees[i].lastName;
            delete[] employees[i].phoneNumber;
        }

        delete[] employees;
        employees = nullptr;  
    }

    size = 0;
    cout << "Memory cleaned up successfully.\n";
}

int main()
{
    system("chcp 1251");

    Employee* employees = nullptr;
    size_t size = 0;

    cout << "Loading data from file...\n";
    loadFromFile(employees, size, "data.txt");

    cout << "Reached the end of loading data from file function.\n";

    while (true)
    {
        cout << "========== Employee Information System ==========\n";
        cout << "1. Display all employees\n";
        cout << "2. Search by last name\n";
        cout << "3. Search by salary range\n";
        cout << "4. Sort by last name\n";
        cout << "5. Add a new employee\n";
        cout << "6. Remove an employee\n";
        cout << "7. Exit\n";
        cout << "=================================================\n";

        int choice;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Displaying all employees...\n";
            displayAllEmployees(employees, size);
            break;
        case 2:
            cout << "Searching by last name...\n";
            searchByLastName(employees, size);
            break;
        case 3:
            cout << "Searching by salary range... (not implemented)\n";
            searchBySalaryRange(employees, size);
            break;
        case 4:
            cout << "Sorting by last name...\n";
            sortByLastName(employees, size);
            displayAllEmployees(employees, size);
            break;
        case 5:
            addEmployee(employees, size);
            break;
        case 6:
            cout << "Removing an employee...\n";
            removeEmployee(employees, size);
            saveToFile(employees, size, "data.txt"); 
            break;
        case 7:
            cout << "Exiting the program. Goodbye!\n";
            cleanupMemory(employees, size);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
            break;
        }
    }

    return 0;
}
