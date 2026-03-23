/*
 * Project: University Library Management System
 * Course: CS112 - Computer Programming 2
 * Team: Hood Research Department (Alcantara, Bonggay, Epong, Sarmago)
 * Date: March 27, 2026
 * Description: A modular management system using C++ Vectors and Structs 
 * to handle material circulation and student fine assessments.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- Structs (Data Encapsulation) ---

/**
 * @struct Student
 * @brief Encapsulates patron data for the library system.
 */
struct Student {
    string idNumber;
    string name;
    double unpaidFines;
};

/**
 * @struct Material
 * @brief Encapsulates library resource data.
 */
struct Material {
    string accessionNum;
    string title;
    string author;
    bool isAvailable;
};

// --- Global Vectors (Dynamic Arrays) ---
vector<Student> students;
vector<Material> library;

// --- Function Prototypes ---
void initLibrary();
int findStudent(string id);
int findMaterial(string accessionNum);

void adminMenu();
void addMaterial();
void viewLibrary();
void displaySortedStudents();
void displayStudent(string id);
void viewLibraryStats(); 

void studentMenu();
void registerStudent();
void settleAccount(int index);
void borrowMaterial(int index);
void returnMaterial(int index);

// --- Main Program ---

/**
 * @brief Entry point of the application.
 * @logic Implements a persistent loop for menu navigation.
 * @efficiency Uses cin.clear() and cin.ignore() to catch non-numeric 
 * terminal inputs, satisfying the requirement to handle all wrong inputs.
 */
int main() {
    initLibrary();
    int option;

    while (true) {
        cout << "\n=========================================\n";
        cout << "            UNIVERSITY LIBRARY           \n";
        cout << "=========================================\n";
        cout << "Login as:\n1. Library Admin\n2. Student\n0. Exit\nChoice: ";
        
        // Input validation: Prevents infinite loop if a letter is typed
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (option == 0) {
            cout << "Exiting system. Goodbye!\n";
            break;
        } else if (option == 1) {
            adminMenu();
        } else if (option == 2) {
            studentMenu();
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}

// --- Initialization & Utilities ---

/**
 * @brief Initializes the system with default library data.
 * @logic Uses std::vector::push_back to populate the library with baseline Material objects.
 */
void initLibrary() {
    library.push_back({"LRC-0001001", "C++ Primer", "Stanley Lippman", true});
    library.push_back({"LRC-0001002", "Clean Code", "Robert C. Martin", true});
    library.push_back({"LRC-0001003", "University Physics", "Young & Freedman", true});
    library.push_back({"LRC-0001004", "Data Structures & Algorithms", "Mark Allen Weiss", true});
}

/**
 * @brief Performs a Linear Search to locate a student record.
 * @param id The 10-digit numeric string to search for.
 * @return The integer index in the vector if found; -1 otherwise.
 * @reusability Can be called by any module needing to verify a student's existence.
 */
int findStudent(string id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].idNumber == id) return i;
    }
    return -1; // Not found
}

/**
 * @brief Performs a Linear Search to locate a library material.
 * @param accessionNum The LRC-XXXXXXX formatted string.
 * @return The integer index in the vector if found; -1 otherwise.
 * @reusability Independent routine used for checking duplicates and processing returns.
 */
int findMaterial(string accessionNum) {
    for (int i = 0; i < library.size(); i++) {
        if (library[i].accessionNum == accessionNum) return i;
    }
    return -1; // Not found
}

// --- Admin Functions ---

/**
 * @brief Primary interface for administrative tasks.
 * @logic Implements simple string-based gatekeeper authentication. Uses a switch-case
 * routing system to access administrative sub-routines.
 */
void adminMenu() {
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;
    
    if (password != "admin123") {
        cout << "Access Denied. Incorrect password.\n";
        return;
    }

    int option;
    while (true) {
        cout << "\n--- Library Admin Dashboard ---\n";
        cout << "1. Add New Material\n2. View Entire Catalog\n3. View Student Roster (Sorted by ID)\n4. Check Student Fines\n5. View library Statistics\n0. Logout\nChoice: ";
        cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1: addMaterial(); break;
            case 2: viewLibrary(); break;
            case 3: displaySortedStudents(); break;
            case 4: {
                string id;
                cout << "Enter Student ID Number: ";
                cin >> id;
                displayStudent(id);
                break;
            }
            case 5: viewLibraryStats(); break;
            default: cout << "Invalid option.\n";
        }
    }
}

/**
 * @brief Handles the creation and validation of new library materials.
 * @efficiency Implements a strict while(true) validation loop to intercept formatting 
 * errors, character mismatches, and duplicate entries without crashing.
 */
void addMaterial() {
    Material m;

    while (true) {
        cout << "Enter Accession Number (Format: LRC-XXXXXXX): ";
        cin >> m.accessionNum;

        // 1. Length Validation (LRC- + 7 digits = 11 characters)
        if (m.accessionNum.length() != 11) {
            cout << "Error: Invalid length. Follow the format LRC-XXXXXXX.\n";
            continue;
        }

        // 2. Prefix Validation (Checking the first 4 characters)
        if (m.accessionNum.substr(0, 4) != "LRC-") {
            cout << "Error: Must start with 'LRC-'.\n";
            continue;
        }

        // 3. Digits Validation (Checking the rest of the string)
        bool validDigits = true;
        for (int i = 4; i < m.accessionNum.length(); i++) {
            if (!isdigit(m.accessionNum[i])) {
                validDigits = false;
                break;
            }
        }

        if (!validDigits) {
            cout << "Error: The part after 'LRC-' must be numeric.\n";
            continue;
        }

        // 4. Uniqueness Check
        if (findMaterial(m.accessionNum) != -1) {
            cout << "Error: This material already exists in the LRC.\n";
            continue;
        }

        break; // All checks passed
    }

    cout << "Enter material title: ";
    cin.ignore();
    getline(cin, m.title);

    cout << "Enter author name: ";
    getline(cin, m.author);

    m.isAvailable = true;
    library.push_back(m);
    cout << "Material successfully added to the library catalog.\n";
}

/**
 * @brief Renders the entire library catalog to the console.
 * @logic Traverses the vector and uses ternary operators to format the availability output.
 */
void viewLibrary() {
    cout << "\n--- Library Catalog ---\n";
    for (int i = 0; i < library.size(); i++) {
        cout << "Accession No: " << library[i].accessionNum 
             << " | Title: " << library[i].title 
             << " | Author: " << library[i].author 
             << " | Available: " << (library[i].isAvailable ? "Yes" : "Out on Loan") << "\n";
    }
}

/**
 * @brief Sorts and displays students by ID Number for the Roster view.
 * @algorithm Bubble Sort Implementation.
 * Uses a nested for-loop structure (O(n^2)). It compares adjacent student ID strings
 * and performs a 'swap' using a temporary Student object.
 */
void displaySortedStudents() {
    if (students.empty()) {
        cout << "\nNo students currently registered.\n";
        return;
    }

    // --- Bubble Sort Algorithm ---
    // 1. Compare adjacent student IDs.
    // 2. Swap if the left ID is lexicographically greater than the right.
    // 3. Repeat until the largest ID "bubbles" to the end of the vector.
    vector<Student> sorted = students;
    int n = sorted.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j].idNumber > sorted[j + 1].idNumber) {
                // Swap the structs
                Student temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    cout << "\n--- Registered Students (Sorted by ID) ---\n";
    for (int i = 0; i < sorted.size(); i++) {
        cout << "ID No: " << sorted[i].idNumber << " | Name: " << sorted[i].name 
             << " | Unpaid Fines: P" << fixed << setprecision(2) << sorted[i].unpaidFines << "\n";
    }
}

/**
 * @brief Retrieves and formats a specific student's profile.
 * @param id The unique 10-digit ID string.
 */
void displayStudent(string id) {
    int index = findStudent(id);
    if (index == -1) {
        cout << "Student not found in database.\n";
        return;
    }
    cout << "\n--- Student Record ---\n"
         << "ID No: " << students[index].idNumber << "\n"
         << "Name: " << students[index].name << "\n"
         << "Unpaid Fines: P" << fixed << setprecision(2) << students[index].unpaidFines << "\n";
}

/**
 * @brief Aggregates system-wide data to provide a snapshot of library stock.
 * @logic Uses accumulators across multiple vectors to compile statistics.
 */
void viewLibraryStats() {
    int totalMaterials = library.size();
    int availableCount = 0;
    double totalFinesOwed = 0.00;

    for (int i = 0; i < library.size(); i++) {
        if (library[i].isAvailable) availableCount++;
    }

    for (int i = 0; i < students.size(); i++) {
        totalFinesOwed += students[i].unpaidFines;
    }

    cout << "\n--- Library Statistics ---\n";
    cout << "Total Materials Owned: " << totalMaterials << "\n";
    cout << "Materials Currently Available: " << availableCount << "\n";
    cout << "Materials Out on Loan: " << (totalMaterials - availableCount) << "\n";
    cout << "Total Outstanding Fines: P" << fixed << setprecision(2) << totalFinesOwed << "\n";

    if (!students.empty()) {
    cout << "Average Fine per Student: P" << (totalFinesOwed / students.size()) << "\n";
    }
}

// --- Student Functions ---

/**
 * @brief Gateway for student interaction and identification.
 * @logic Branches logic based on whether the student ID is found. If found, passes
 * the vector index to sub-routines to maintain data state.
 */
void studentMenu() {
    string id;
    cout << "Enter your Student ID Number: ";
    cin >> id;

    int index = findStudent(id);
    if (index == -1) {
        int option;
        cout << "ID not recognized. Register for Library Access? (1. Yes / 2. No): ";
        cin >> option;
        if (option == 1) {
            registerStudent();
        }
        return;
    }

    int option;
    while (true) {
        cout << "\n--- Student Portal ---\n";
        cout << "1. View My Record & Fines\n2. Settle Account Fines\n3. Borrow Material\n4. Return Material\n0. Logout\nChoice: ";
        cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1: displayStudent(id); break;
            case 2: settleAccount(index); break;
            case 3: borrowMaterial(index); break;
            case 4: returnMaterial(index); break;
            default: cout << "Invalid option.\n";
        }
    }
}

/**
 * @brief Manages the registration of new student accounts.
 * @efficiency Forces strict 10-digit validation to ensure data consistency and prevent overflow.
 */
void registerStudent() {
    Student s;
    
    // The Validation Loop
    while (true) {
        cout << "Enter Student ID Number (Exactly 10 digits): ";
        cin >> s.idNumber;

        // Rule 1: Must be exactly 10 characters long
        if (s.idNumber.length() != 10) {
            cout << "Error: ID must be exactly 10 digits long. Please try again.\n";
            continue; 
        }

        // Rule 2: Must only contain numbers
        bool isAllDigits = true;
        for (int i = 0; i < s.idNumber.length(); i++) {
            if (!isdigit(s.idNumber[i])) {
                isAllDigits = false;
                break;
            }
        }
        
        if (!isAllDigits) {
            cout << "Error: ID cannot contain letters or symbols. Please try again.\n";
            continue; 
        }

        // Rule 3: Must not already exist in the system
        if (findStudent(s.idNumber) != -1) {
            cout << "Error: This ID is already registered. Please try a different one.\n";
            continue; 
        }

        break; 
    }

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, s.name);

    s.unpaidFines = 0.00; 
    students.push_back(s);
    
    cout << "Registration successful. Welcome to the USTP Library, " << s.name << "!\n";
}

/**
 * @brief Handles fine payments and account balancing.
 * @param index Position of the student in the vector.
 * @logic Includes an 'Overpayment Handler' to calculate change due and prevent negative fines.
 */
void settleAccount(int index) {
    if (students[index].unpaidFines <= 0) {
        cout << "You have no outstanding fines. Thank you for being responsible!\n";
        return;
    }

    double payment;
    cout << "Your current outstanding fines are: P" << fixed << setprecision(2) << students[index].unpaidFines << "\n";
    cout << "Enter payment amount: P";
    cin >> payment;
    
    if (payment <= 0) {
        cout << "Invalid payment amount.\n";
        return;
    }

    students[index].unpaidFines -= payment;
    
    // Prevent negative fines if they overpay
    if (students[index].unpaidFines < 0) {
        cout << "Change due: P" << fixed << setprecision(2) << (students[index].unpaidFines * -1) << "\n";
        students[index].unpaidFines = 0.00;
    }

    cout << "Payment successful. Remaining Fines: P" << fixed << setprecision(2) << students[index].unpaidFines << "\n";
}


/**
 * @brief Authorizes a material loan based on account standing.
 * @param index Position of the student in the vector.
 * @logic Enforces a business rule blocking loans if fines exceed P50.00.
 */
void borrowMaterial(int index) {
    // Strict library Rule: Cannot borrow if fines are over P50.00
    if (students[index].unpaidFines >= 50.00) {
        cout << "Borrowing blocked. You have P" << fixed << setprecision(2) << students[index].unpaidFines 
             << " in unpaid fines. Please settle your account first.\n";
        return;
    }

    cout << "\n--- Available Materials ---\n";
    for (int i = 0; i < library.size(); i++) {
        if (library[i].isAvailable) {
            cout << i + 1 << ". " << library[i].title 
                 << " by " << library[i].author 
                 << " (Accession No: " << library[i].accessionNum << ")\n";
        }
    }

    int choice;
    cout << "Enter the list number of the material to borrow (0 to cancel): ";
    cin >> choice;

    if (choice == 0 || choice > library.size()) return;

    if (library[choice - 1].isAvailable) {
        library[choice - 1].isAvailable = false;
        cout << "Material successfully borrowed. It is free of charge.\n";
        cout << "NOTE: Please return within 7 days to avoid a P10.50 daily late fee.\n";
    } else {
        cout << "Transaction failed. Material is currently unavailable.\n";
    }
}

/**
 * @brief Processes the return of borrowed materials and assesses penalties.
 * @param index Position of the student in the vector.
 * @logic Calculates late fees based on a 7-day allowed borrow period.
 */
void returnMaterial(int index) {
    string accessionNum;
    cout << "Enter the Accession Number of the material you are returning: ";
    cin >> accessionNum;

    int matIndex = findMaterial(accessionNum);
    
    if (matIndex == -1) {
        cout << "Invalid Accession Number.\n";
        return;
    }

    if (library[matIndex].isAvailable == false) {
        int days;
        cout << "How many days did you borrow this material? ";
        cin >> days;

        // Mathematical Function: Penalty calculation
        double penalty = 0.00;
        int allowedDays = 7;
        
        if (days > allowedDays) {
            int daysLate = days - allowedDays;
            penalty = daysLate * 10.50; // P10.50 penalty per day late
            students[index].unpaidFines += penalty;
            
            cout << "\nNotice: Material returned " << daysLate << " days late.\n";
            cout << "A late penalty of P" << fixed << setprecision(2) << penalty << " has been added to your account.\n";
        } else {
            cout << "\nMaterial returned on time. Thank you!\n";
        }

        library[matIndex].isAvailable = true;
        cout << "Current Unpaid Fines: P" << fixed << setprecision(2) << students[index].unpaidFines << "\n";
        
    } else {
        cout << "This material is already listed as available in the library.\n";
    }
}