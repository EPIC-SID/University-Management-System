#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Maximum number of students our system can store in memory
const int MAX_STUDENTS = 100;

// 1. TEMPLATE FUNCTION
// A template function to calculate the average of 3 numbers of any numeric type.
template <typename T>
T sv_calculateAverage(T sv_val1, T sv_val2, T sv_val3) {
    return (sv_val1 + sv_val2 + sv_val3) / static_cast<T>(3);
}

// 2. BASE CLASS (with constructors & virtual function)
// Base class for representing any person in the university system.
class sv_Person {
protected:
    string sv_name;
    int sv_age;

public:
    // Default constructor
    sv_Person() {
        sv_name = "Unknown Person";
        sv_age = 0;
    }

    // Parameterized constructor
    sv_Person(string sv_pName, int sv_pAge) {
        sv_name = sv_pName;
        sv_age = sv_pAge;
    }

    // Virtual destructor - important for cleanup
    virtual ~sv_Person() {}

    // Getters
    string sv_getName() const { return sv_name; }
    int sv_getAge() const { return sv_age; }

    // Virtual function to display information.
    virtual void sv_displayInfo() {
        cout << "Name: " << sv_name << endl;
        cout << "Age: " << sv_age << " years old" << endl;
    }
};

// 3. DERIVED CLASS (with inheritance & overloading)
// Student class inherits from Person
class sv_Student : public sv_Person {
private:
    string sv_prn;
    string sv_course;
    int sv_attendanceDays;
    int sv_totalDays;
    double sv_marks1;
    double sv_marks2;
    double sv_marks3;
    double sv_totalFees;
    double sv_feesPaid;

public:
    // Default constructor
    sv_Student() : sv_Person() {
        sv_prn = "";
        sv_course = "None";
        sv_attendanceDays = 0;
        sv_totalDays = 0;
        sv_marks1 = 0.0;
        sv_marks2 = 0.0;
        sv_marks3 = 0.0;
        sv_totalFees = 0.0;
        sv_feesPaid = 0.0;
    }

    // Parameterized constructor calling the base class constructor
    sv_Student(string sv_sName, int sv_sAge, string sv_sPrn, string sv_sCourse, double sv_sTotalFees)
        : sv_Person(sv_sName, sv_sAge) {
        sv_prn = sv_sPrn;
        sv_course = sv_sCourse;
        sv_attendanceDays = 0;
        sv_totalDays = 0;
        sv_marks1 = 0.0;
        sv_marks2 = 0.0;
        sv_marks3 = 0.0;
        sv_totalFees = sv_sTotalFees;
        sv_feesPaid = 0.0;
    }

    // Getters
    string sv_getPrn() const { return sv_prn; }
    string sv_getCourse() const { return sv_course; }
    int sv_getAttendanceDays() const { return sv_attendanceDays; }
    int sv_getTotalDays() const { return sv_totalDays; }
    double sv_getMarks1() const { return sv_marks1; }
    double sv_getMarks2() const { return sv_marks2; }
    double sv_getMarks3() const { return sv_marks3; }
    double sv_getTotalFees() const { return sv_totalFees; }
    double sv_getFeesPaid() const { return sv_feesPaid; }

    // Setters
    void sv_setMarks(double sv_m1, double sv_m2, double sv_m3) {
        sv_marks1 = sv_m1;
        sv_marks2 = sv_m2;
        sv_marks3 = sv_m3;
    }

    // Helper to load database details directly
    void sv_setDatabaseInfo(string sv_sPrn, string sv_sName, int sv_sAge, string sv_sCourse,
                            int sv_attDays, int sv_totDays, double sv_m1, double sv_m2, double sv_m3,
                            double sv_totFees, double sv_feesPaid) {
        sv_prn = sv_sPrn;
        sv_name = sv_sName;
        sv_age = sv_sAge;
        sv_course = sv_sCourse;
        sv_attendanceDays = sv_attDays;
        sv_totalDays = sv_totDays;
        sv_marks1 = sv_m1;
        sv_marks2 = sv_m2;
        sv_marks3 = sv_m3;
        sv_totalFees = sv_totFees;
        sv_feesPaid = sv_feesPaid;
    }

    // Pay fees
    void sv_payFees(double sv_amount) {
        sv_feesPaid += sv_amount;
    }

    // Get remaining fee balance
    double sv_getFeeBalance() const {
        return sv_totalFees - sv_feesPaid;
    }

    // Get attendance percentage
    double sv_getAttendancePercentage() const {
        if (sv_totalDays == 0) return 0.0;
        return (static_cast<double>(sv_attendanceDays) / sv_totalDays) * 100.0;
    }

    // 4. FUNCTION OVERLOADING
    // Version 1: Mark attendance with just the number of days attended
    void sv_markAttendance(int sv_daysAttended) {
        sv_attendanceDays += sv_daysAttended;
        sv_totalDays += sv_daysAttended;
    }

    // Version 2: Mark attendance with both days attended and days missed
    void sv_markAttendance(int sv_daysAttended, int sv_daysMissed) {
        sv_attendanceDays += sv_daysAttended;
        sv_totalDays += (sv_daysAttended + sv_daysMissed);
    }

    // 5. VIRTUAL FUNCTION OVERRIDING
    // Overriding the base class display function
    void sv_displayInfo() override {
        cout << "---------------------------------------------------" << endl;
        cout << "               STUDENT REPORT CARD                 " << endl;
        cout << "---------------------------------------------------" << endl;
        sv_Person::sv_displayInfo();
        
        cout << "PRN           : " << sv_prn << endl;
        cout << "Course        : " << sv_course << endl;
        cout << "Attendance    : " << sv_attendanceDays << "/" << sv_totalDays
             << " (" << sv_getAttendancePercentage() << "%)" << endl;
        
        cout << "Exam Scores   : " << sv_marks1 << ", " << sv_marks2 << ", " << sv_marks3 << endl;
        double sv_avg = sv_calculateAverage(sv_marks1, sv_marks2, sv_marks3);
        cout << "Average Score : " << sv_avg << endl;
        
        cout << "Total Tuition : Rs. " << sv_totalFees << endl;
        cout << "Fees Paid     : Rs. " << sv_feesPaid << endl;
        cout << "Fee Balance   : Rs. " << sv_getFeeBalance() << endl;
        cout << "---------------------------------------------------" << endl;
    }

    // Save student details directly to file stream using single lines for simplicity
    void sv_saveToFile(ofstream& sv_outFile) const {
        sv_outFile << sv_prn << "\n"
                   << sv_name << "\n"
                   << sv_age << "\n"
                   << sv_course << "\n"
                   << sv_attendanceDays << "\n"
                   << sv_totalDays << "\n"
                   << sv_marks1 << "\n"
                   << sv_marks2 << "\n"
                   << sv_marks3 << "\n"
                   << sv_totalFees << "\n"
                   << sv_feesPaid << "\n";
    }
};

// 6. HELPER FUNCTIONS & FILE HANDLING

// Function demonstrating runtime polymorphism using a base class pointer
void sv_printPolymorphicDetails(sv_Person* sv_p) {
    sv_p->sv_displayInfo();
}

// Clear the terminal input buffer to prevent errors
void sv_clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Save all student objects to database file
void sv_saveToDatabase(const sv_Student sv_list[], int sv_count) {
    ofstream sv_outFile("sv_database.txt");
    if (!sv_outFile) {
        cout << "[Error] Could not open sv_database.txt for writing!" << endl;
        return;
    }
    for (int sv_i = 0; sv_i < sv_count; ++sv_i) {
        sv_list[sv_i].sv_saveToFile(sv_outFile);
    }
    sv_outFile.close();
}

// Load all student objects from database file
void sv_loadFromDatabase(sv_Student sv_list[], int& sv_count) {
    ifstream sv_inFile("sv_database.txt");
    if (!sv_inFile) {
        sv_count = 0;
        return;
    }
    sv_count = 0;
    string sv_prn;
    while (sv_count < MAX_STUDENTS && getline(sv_inFile, sv_prn)) {
        if (sv_prn.empty()) continue;
        
        string sv_name, sv_temp, sv_course;
        getline(sv_inFile, sv_name);
        
        getline(sv_inFile, sv_temp);
        int sv_age = stoi(sv_temp);
        
        getline(sv_inFile, sv_course);
        
        getline(sv_inFile, sv_temp);
        int sv_attDays = stoi(sv_temp);
        
        getline(sv_inFile, sv_temp);
        int sv_totDays = stoi(sv_temp);
        
        getline(sv_inFile, sv_temp);
        double sv_m1 = stod(sv_temp);
        
        getline(sv_inFile, sv_temp);
        double sv_m2 = stod(sv_temp);
        
        getline(sv_inFile, sv_temp);
        double sv_m3 = stod(sv_temp);
        
        getline(sv_inFile, sv_temp);
        double sv_totFees = stod(sv_temp);
        
        getline(sv_inFile, sv_temp);
        double sv_feesPaid = stod(sv_temp);
        
        sv_list[sv_count].sv_setDatabaseInfo(sv_prn, sv_name, sv_age, sv_course, 
                                             sv_attDays, sv_totDays, sv_m1, sv_m2, sv_m3, 
                                             sv_totFees, sv_feesPaid);
        sv_count++;
    }
    sv_inFile.close();
    cout << "[System] Loaded " << sv_count << " student records from database." << endl;
}

// Export a report card of all students to a text file
void sv_exportReportCards(const sv_Student sv_list[], int sv_count) {
    ofstream sv_reportFile("sv_report_card.txt");
    if (!sv_reportFile) {
        cout << "[Error] Could not create sv_report_card.txt!" << endl;
        return;
    }

    sv_reportFile << "=================================================================\n";
    sv_reportFile << "             UNIVERSITY STUDENT MANAGEMENT REPORT                \n";
    sv_reportFile << "=================================================================\n\n";

    for (int sv_i = 0; sv_i < sv_count; ++sv_i) {
        const sv_Student& sv_stud = sv_list[sv_i];
        sv_reportFile << "PRN: " << sv_stud.sv_getPrn() << "\n";
        sv_reportFile << "Name: " << sv_stud.sv_getName() << " | Age: " << sv_stud.sv_getAge() << "\n";
        sv_reportFile << "Course: " << sv_stud.sv_getCourse() << "\n";
        
        sv_reportFile << "Attendance: " << sv_stud.sv_getAttendanceDays() << "/" << sv_stud.sv_getTotalDays()
                      << " (" << sv_stud.sv_getAttendancePercentage() << "%)\n";
                      
        double sv_avg = sv_calculateAverage(sv_stud.sv_getMarks1(), sv_stud.sv_getMarks2(), sv_stud.sv_getMarks3());
        sv_reportFile << "Marks: Sub1: " << sv_stud.sv_getMarks1() 
                      << " | Sub2: " << sv_stud.sv_getMarks2() 
                      << " | Sub3: " << sv_stud.sv_getMarks3() << "\n";
        sv_reportFile << "Average Mark: " << sv_avg << "\n";
        
        sv_reportFile << "Fees: Total: Rs. " << sv_stud.sv_getTotalFees() 
                      << " | Paid: Rs. " << sv_stud.sv_getFeesPaid() 
                      << " | Balance: Rs. " << sv_stud.sv_getFeeBalance() << "\n";
        sv_reportFile << "-----------------------------------------------------------------\n\n";
    }

    sv_reportFile.close();
    cout << "[System] Detailed reports generated in 'sv_report_card.txt'!" << endl;
}

// 7. MAIN INTERACTION LOOP
int main() {
    sv_Student sv_students[MAX_STUDENTS];
    int sv_studentCount = 0;
    
    // Load existing records from file on start
    sv_loadFromDatabase(sv_students, sv_studentCount);

    int sv_choice = 0;

    cout << "========================================================" << endl;
    cout << "      Welcome to University Student Management System   " << endl;
    cout << "========================================================" << endl;

    while (true) {
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1. New Student Admission (Create Record)" << endl;
        cout << "2. Mark Attendance" << endl;
        cout << "3. Enter Examination Results" << endl;
        cout << "4. Process Fee Payment" << endl;
        cout << "5. Display Specific Student (Polymorphic View)" << endl;
        cout << "6. Display All Students" << endl;
        cout << "7. Export Report Cards to Text File" << endl;
        cout << "8. View Report Cards File Contents" << endl;
        cout << "9. Save & Exit" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> sv_choice)) {
            cout << "Please enter a valid choice number." << endl;
            sv_clearInput();
            continue;
        }

        if (sv_choice == 9) {
            sv_saveToDatabase(sv_students, sv_studentCount);
            cout << "\nThank you for using the system. Goodbye!" << endl;
            break;
        }

        switch (sv_choice) {
            case 1: {
                if (sv_studentCount >= MAX_STUDENTS) {
                    cout << "[Error] Student database limit reached. Cannot add more students." << endl;
                    break;
                }

                string sv_nameInput, sv_courseInput;
                int sv_ageInput;
                string sv_prnInput;
                double sv_feesInput;

                cout << "\n--- Student Admission Portal ---" << endl;
                cout << "Enter PRN: ";
                cin >> sv_prnInput;

                // Check if PRN already exists
                bool sv_exists = false;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    if (sv_students[sv_i].sv_getPrn() == sv_prnInput) {
                        sv_exists = true;
                        break;
                    }
                }
                if (sv_exists) {
                    cout << "[Error] Student with PRN " << sv_prnInput << " already exists!" << endl;
                    break;
                }

                sv_clearInput(); // clear before getline
                cout << "Enter Full Name: ";
                getline(cin, sv_nameInput);

                cout << "Enter Age: ";
                if (!(cin >> sv_ageInput)) {
                    cout << "[Error] Age must be a number." << endl;
                    sv_clearInput();
                    break;
                }

                sv_clearInput();
                cout << "Enter Course Name: ";
                getline(cin, sv_courseInput);

                cout << "Enter Semester Fee Amount: Rs. ";
                if (!(cin >> sv_feesInput)) {
                    cout << "[Error] Fee must be a number." << endl;
                    sv_clearInput();
                    break;
                }

                // Create a student using parameterized constructor
                sv_Student sv_newStud(sv_nameInput, sv_ageInput, sv_prnInput, sv_courseInput, sv_feesInput);
                sv_students[sv_studentCount] = sv_newStud;
                sv_studentCount++;
                
                sv_saveToDatabase(sv_students, sv_studentCount);
                cout << "[Success] Student registered successfully!" << endl;
                break;
            }

            case 2: {
                if (sv_studentCount == 0) {
                    cout << "No students registered yet." << endl;
                    break;
                }

                string sv_prnSearch;
                cout << "\nEnter student PRN to mark attendance: ";
                cin >> sv_prnSearch;

                int sv_index = -1;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    if (sv_students[sv_i].sv_getPrn() == sv_prnSearch) {
                        sv_index = sv_i;
                        break;
                    }
                }

                if (sv_index == -1) {
                    cout << "[Error] Student not found." << endl;
                    break;
                }

                cout << "How do you want to input attendance?" << endl;
                cout << "1. Only days attended (assume 0 missed)" << endl;
                cout << "2. Days attended AND days missed" << endl;
                int sv_attChoice;
                if (!(cin >> sv_attChoice) || (sv_attChoice != 1 && sv_attChoice != 2)) {
                    cout << "[Error] Invalid choice." << endl;
                    sv_clearInput();
                    break;
                }

                if (sv_attChoice == 1) {
                    int sv_attDays;
                    cout << "Enter days attended: ";
                    if (!(cin >> sv_attDays)) {
                        cout << "[Error] Invalid number of days." << endl;
                        sv_clearInput();
                        break;
                    }
                    sv_students[sv_index].sv_markAttendance(sv_attDays);
                    cout << "[Success] Attendance updated." << endl;
                } else {
                    int sv_attDays, sv_missDays;
                    cout << "Enter days attended: ";
                    if (!(cin >> sv_attDays)) {
                        cout << "[Error] Invalid number of days." << endl;
                        sv_clearInput();
                        break;
                    }
                    cout << "Enter days missed: ";
                    if (!(cin >> sv_missDays)) {
                        cout << "[Error] Invalid number of days." << endl;
                        sv_clearInput();
                        break;
                    }
                    sv_students[sv_index].sv_markAttendance(sv_attDays, sv_missDays);
                    cout << "[Success] Attendance updated." << endl;
                }
                
                sv_saveToDatabase(sv_students, sv_studentCount);
                break;
            }

            case 3: {
                if (sv_studentCount == 0) {
                    cout << "No students registered yet." << endl;
                    break;
                }

                string sv_prnSearch;
                cout << "\nEnter student PRN to update marks: ";
                cin >> sv_prnSearch;

                int sv_index = -1;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    if (sv_students[sv_i].sv_getPrn() == sv_prnSearch) {
                        sv_index = sv_i;
                        break;
                    }
                }

                if (sv_index == -1) {
                    cout << "[Error] Student not found." << endl;
                    break;
                }

                double sv_m1, sv_m2, sv_m3;
                cout << "Enter Marks for Subject 1: ";
                if (!(cin >> sv_m1)) { cout << "[Error] Invalid mark."; sv_clearInput(); break; }
                cout << "Enter Marks for Subject 2: ";
                if (!(cin >> sv_m2)) { cout << "[Error] Invalid mark."; sv_clearInput(); break; }
                cout << "Enter Marks for Subject 3: ";
                if (!(cin >> sv_m3)) { cout << "[Error] Invalid mark."; sv_clearInput(); break; }

                sv_students[sv_index].sv_setMarks(sv_m1, sv_m2, sv_m3);
                cout << "[Success] Examination marks updated." << endl;
                
                sv_saveToDatabase(sv_students, sv_studentCount);
                break;
            }

            case 4: {
                if (sv_studentCount == 0) {
                    cout << "No students registered yet." << endl;
                    break;
                }

                string sv_prnSearch;
                cout << "\nEnter student PRN to pay fees: ";
                cin >> sv_prnSearch;

                int sv_index = -1;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    if (sv_students[sv_i].sv_getPrn() == sv_prnSearch) {
                        sv_index = sv_i;
                        break;
                    }
                }

                if (sv_index == -1) {
                    cout << "[Error] Student not found." << endl;
                    break;
                }

                cout << "Current Fee Status: " << endl;
                cout << "  Total Fees : Rs. " << sv_students[sv_index].sv_getTotalFees() << endl;
                cout << "  Paid       : Rs. " << sv_students[sv_index].sv_getFeesPaid() << endl;
                cout << "  Balance    : Rs. " << sv_students[sv_index].sv_getFeeBalance() << endl;

                double sv_payAmt;
                cout << "Enter amount to pay: Rs. ";
                if (!(cin >> sv_payAmt) || sv_payAmt <= 0) {
                    cout << "[Error] Payment amount must be a positive number." << endl;
                    sv_clearInput();
                    break;
                }

                if (sv_payAmt > sv_students[sv_index].sv_getFeeBalance()) {
                    cout << "[Warning] Amount exceeds remaining balance. Paying only the remaining balance: Rs. " 
                         << sv_students[sv_index].sv_getFeeBalance() << endl;
                    sv_payAmt = sv_students[sv_index].sv_getFeeBalance();
                }

                sv_students[sv_index].sv_payFees(sv_payAmt);
                cout << "[Success] Payment processed!" << endl;
                
                sv_saveToDatabase(sv_students, sv_studentCount);
                break;
            }

            case 5: {
                if (sv_studentCount == 0) {
                    cout << "No students registered yet." << endl;
                    break;
                }

                string sv_prnSearch;
                cout << "\nEnter student PRN to view report: ";
                cin >> sv_prnSearch;

                int sv_index = -1;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    if (sv_students[sv_i].sv_getPrn() == sv_prnSearch) {
                        sv_index = sv_i;
                        break;
                    }
                }

                if (sv_index == -1) {
                    cout << "[Error] Student not found." << endl;
                    break;
                }

                // Polymorphism test
                sv_Person* sv_personPtr = &sv_students[sv_index];
                cout << "\nLoading..." << endl;
                sv_printPolymorphicDetails(sv_personPtr);
                break;
            }

            case 6: {
                if (sv_studentCount == 0) {
                    cout << "No student records found." << endl;
                    break;
                }

                cout << "\nDisplaying all " << sv_studentCount << " students:" << endl;
                for (int sv_i = 0; sv_i < sv_studentCount; ++sv_i) {
                    sv_Person* sv_p = &sv_students[sv_i];
                    sv_printPolymorphicDetails(sv_p);
                }
                break;
            }

            case 7: {
                if (sv_studentCount == 0) {
                    cout << "No students to generate reports for." << endl;
                    break;
                }
                sv_exportReportCards(sv_students, sv_studentCount);
                break;
            }

            case 8: {
                ifstream sv_inFile("sv_report_card.txt");
                if (!sv_inFile) {
                    cout << "[System] No export file 'sv_report_card.txt' found. Please choose Option 7 first." << endl;
                    break;
                }
                cout << "\n--- READING FROM REPORT FILE (sv_report_card.txt) ---" << endl;
                string sv_fileLine;
                while (getline(sv_inFile, sv_fileLine)) {
                    cout << sv_fileLine << endl;
                }
                sv_inFile.close();
                cout << "-----------------------------------------------------" << endl;
                break;
            }

            default:
                cout << "Invalid selection! Please enter a choice between 1 and 9." << endl;
                break;
        }
    }

    return 0;
}
