# University Student Management System

This is a C++ console application for managing a university student database. It allows you to add student admissions, mark attendance, enter exam scores, process fee payments, and view student reports. 

I wrote this program to cover all the Object-Oriented Programming (OOP) concepts we learned in class. All variable and class attribute names start with the "sv_" prefix.

## OOP Concepts Implemented

1. **Constructors**: Standard and parameterized constructors are used. The student class constructor calls the base class constructor using initializer lists.
2. **Inheritance**: The student class (`sv_Student`) inherits from the base person class (`sv_Person`).
3. **Function Overloading**: The `sv_markAttendance` function is overloaded to support two different input methods:
   - One argument for days attended.
   - Two arguments for days attended and days missed.
4. **Virtual Functions**: The `sv_displayInfo` method in the base class is virtual and is overridden in the student class to show details polymorphic style using a base class pointer.
5. **Templates**: A template function `sv_calculateAverage` calculates the average of three values.
6. **File Handling**: The system saves database records to `sv_database.txt` on exit and loads them back on startup. It also exports report cards to `sv_report_card.txt`.

## Features

- Add new student records with unique roll numbers.
- Track attendance (uses overloaded methods).
- Store 3 subject exam marks and calculate average scores.
- Pay tuition fees (shows remaining balance in Rupees).
- View student details on screen or read from the exported file.

## Files in this Project

- `main.cpp`: The complete C++ source code file.
- `sv_database.txt`: Saves student data in comma-separated lines.
- `sv_report_card.txt`: Contains exported formatted report cards.

## Compilation and Execution

To compile the program, run this command:
```bash
g++ main.cpp -o main
```

To run the program:
```bash
./main
```