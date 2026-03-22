#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Student {
    int roll;
    string name;
    double balance;
};
struct Book {
    string title;
    string author;
    int isbn;
    bool available;
};

vector<Student> students;
vector<Book> books;

void initBooks();
int findStudent(int roll);
int findBook(int isbn);

void adminMenu();
void addBook();
void editBook();
void viewBooks();
void displaySortedStudents();
void displayStudent(int roll);

void studentMenu();
void createAccount();
void depositAmount(int index);
void issueItem(int index);

int main() {
    initBooks();
    int option;

    while (true) {
        cout << "\n--- Library Management System ---\n";
        cout << "Login as:\n1. Admin\n2. Student\n0. Exit\nChoice: ";
        if (!(cin >> option)) break;

        if (option == 0) {
            break;
        } else if (option == 1) {
            string password;
            cout << "Enter password: ";
            cin >> password;
            
            if (password == "password") {
                adminMenu();
            } else {
                cout << "Incorrect password.\n";
            }
        } else if (option == 2) {
            studentMenu();
        } else {
            cout << "Invalid option.\n";
        }
    }
    return 0;
}

// --- Initialization & Utilities ---
void initBooks() {
    for (int i = 0; i < 15; i++) {
        books.push_back({"Title " + to_string(i+1), "Author", 1000 + i, true});
    }
}

int findStudent(int roll) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) return i;
    }
    return -1;
}

int findBook(int isbn) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].isbn == isbn) return i;
    }
    return -1;
}

// --- Admin Functions ---
void adminMenu() {
    int option;
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add book\n2. Edit book\n3. View book status\n4. View enrolled students\n5. View student balance\n0. Logout\nChoice: ";
        cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1: addBook(); break;
            case 2: editBook(); break;
            case 3: viewBooks(); break;
            case 4: displaySortedStudents(); break;
            case 5: {
                int roll;
                cout << "Enter student roll number: ";
                cin >> roll;
                displayStudent(roll);
                break;
            }
            default: cout << "Invalid option.\n";
        }
    }
}

void addBook() {
    Book b;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, b.title);

    cout << "Enter book author: ";
    getline(cin, b.author);

    cout << "Enter book ISBN: ";
    cin >> b.isbn;

    if (findBook(b.isbn) != -1) {
        cout << "A book with this ISBN already exists.\n";
        return;
    }

    b.available = true;
    books.push_back(b);
    cout << "Book added successfully.\n";
}

void editBook() {
    int isbn;
    cout << "Enter book ISBN to edit: ";
    cin >> isbn;
    
    int index = findBook(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    cout << "Current book title: " << books[index].title << "\n";
    cout << "Enter new book title: ";
    cin.ignore();
    getline(cin, books[index].title);

    cout << "Current book author: " << books[index].author << "\n";
    cout << "Enter new book author: ";
    getline(cin, books[index].author);

    cout << "Book details updated.\n";
}

void viewBooks() {
    for (const auto& book : books) {
        cout << "Title: " << book.title 
             << " | Author: " << book.author 
             << " | ISBN: " << book.isbn 
             << " | Available: " << (book.available ? "Yes" : "No") << "\n";
    }
}

void displaySortedStudents() {
    if (students.empty()) {
        cout << "No students enrolled.\n";
        return;
    }

    vector<Student> sortedStudents = students;
    
    sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
        return a.roll < b.roll;
    });

    for (const auto& s : sortedStudents) {
        cout << s.roll << " - " << s.name << " - Balance: $" << fixed << setprecision(2) << s.balance << "\n";
    }
}

void displayStudent(int roll) {
    int index = findStudent(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }
    cout << "Roll No: " << students[index].roll << "\n"
         << "Name: " << students[index].name << "\n"
         << "Balance: $" << fixed << setprecision(2) << students[index].balance << "\n";
}

// --- Student Functions ---
void studentMenu() {
    int roll;
    cout << "Enter your roll number: ";
    cin >> roll;

    int index = findStudent(roll);
    if (index == -1) {
        int option;
        cout << "Student not found. Create an account? (1. Yes / 2. No): ";
        cin >> option;
        if (option == 1) {
            createAccount();
        }
        return;
    }

    int option;
    while (true) {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View balance\n2. Deposit amount\n3. Issue item\n0. Logout\nChoice: ";
        cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1: displayStudent(roll); break;
            case 2: depositAmount(index); break;
            case 3: issueItem(index); break;
            default: cout << "Invalid option.\n";
        }
    }
}

void createAccount() {
    Student s;
    cout << "Enter roll number (e.g., 101): ";
    cin >> s.roll;

    if (findStudent(s.roll) != -1) {
        cout << "Account already exists for this roll number.\n";
        return;
    }

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, s.name);

    double initial_deposit;
    cout << "Enter initial deposit amount ($50 minimum): ";
    cin >> initial_deposit;

    if (initial_deposit < 50) {
        cout << "Initial deposit must be at least $50.\n";
        return;
    }

    // Account opening and security deposit deduction
    s.balance = initial_deposit - 20 - 30; 
    students.push_back(s);
    
    cout << "Account created successfully!\n";
}

void depositAmount(int index) {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    students[index].balance += amount;
    cout << "New balance: $" << fixed << setprecision(2) << students[index].balance << "\n";
}

void issueItem(int index) {
    cout << "Available books:\n";
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].available) {
            cout << i + 1 << ". " << books[i].title << " by " << books[i].author 
                 << " (ISBN: " << books[i].isbn << ")\n";
        }
    }

    int choice;
    cout << "Enter the number of the book you want to issue (0 to cancel): ";
    cin >> choice;

    if (choice == 0 || choice > books.size()) return;

    if (books[choice - 1].available && students[index].balance >= 2) {
        books[choice - 1].available = false;
        students[index].balance -= 2;
        cout << "Book issued successfully. New balance: $" << fixed << setprecision(2) << students[index].balance << "\n";
    } else {
        cout << "Cannot issue the book. Insufficient balance or book is unavailable.\n";
    }
}