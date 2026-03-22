# University Library Management System in C++

## Project Overview
This University Learning Resource Center (LRC) Management System is a robust console-based application developed in C++ as a Performance Institutional Task (PIT). It is designed to demonstrate mastery of programming fundamentals while implementing modern data structures like structs and vectors to manage library materials, student patron accounts, and overdue fine assessments.

## Technical Specifications & Requirements
This project explicitly fulfills the following CS112 core competencies:

* **Elementary Programming:** Standard I/O operations and data type management.
* **Selections:** Multi-level menu navigation using switch-case and if-else logic.
* **Math & Strings:** Implementation of string manipulation (e.g., `.substr()`, `.length()`) for data validation, and mathematical algorithms for penalty calculations and statistical averages.
* **Loops:** Iterative data processing and a persistent main execution loop.
* **Functions:** Modular code architecture for high readability and maintenance.
* **Advanced Data Structures:** Use of Structures (`struct`) for data encapsulation and Dynamic Arrays (`std::vector`) for scalable storage.

## Key Features

### Multi-Level Authentication
* **Admin Access:** Secured via password. Admins can manage the library catalog, view statistics, and audit sensitive student data.
* **Student Access:** 10-digit ID-based login for personalized account and transaction management.

### Admin Functions
1.  **Catalog Management:** Add new titles to the library with strict alphanumeric validation (Format: `LRC-XXXXXXX`).
2.  **Inventory Tracking:** Real-time visibility of material availability across the entire catalog.
3.  **Member Analytics:** View all registered students sorted by their ID Number using a manual Bubble Sort algorithm.
4.  **Audit Details:** Check specific student profiles and their current outstanding fines.
5.  **System Statistics:** View aggregated LRC data, including active loans, total fines owed, and the average fine per student.

### Student Functions
1.  **Self-Registration:** Create an account requiring a strict 10-digit numeric ID.
2.  **Account Settlement:** View current outstanding fines and process payments (includes overpayment handling to calculate change).
3.  **Transaction System:** Borrow materials free of charge, guarded by a business rule that blocks borrowing if outstanding fines exceed P50.00.
4.  **Smart Returns:** Automated system that calculates Overdue Penalties (P10.50/day) if the material is kept beyond the 7-day grace period.

## Implementation Details

### 1. Data Encapsulation
Unlike standard 2D array implementations, this system uses `struct Student` and `struct Material`. This allows multiple data types (string, double, bool) to be bound together, simulating real-world objects and preventing integer overflow issues with 10-digit IDs.

### 2. Sorting Algorithm
The system implements a manual Bubble Sort to rank student members. This demonstrates a deep understanding of nested loops and memory swapping logic without relying on external libraries.

### 3. Defensive Programming
To ensure the system is "crash-proof" for the PIT presentation, we implemented strict Input Validation. The system clears the `cin` buffer and ignores invalid characters if a user accidentally enters a letter in a numeric field. It also forces persistent `while(true)` loops to guarantee materials and IDs are formatted correctly before being saved.

## How to Compile and Run
1.  **Compiler:** Ensure you have g++ (MinGW/MSYS2) installed.
2.  **Navigate:** Open your terminal in the project folder.
3.  **Compile:**
    ```bash
    g++ -o LibrarySystem main.cpp
    ```
4.  **Execute:**
    ```bash
    ./LibrarySystem
    ```