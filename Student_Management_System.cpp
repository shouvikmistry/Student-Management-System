#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Define a structure to hold student information
struct Student {
    int id;
    string name;
    int age;
    float marks;
};

// Function to add a new student to the file
void addStudent() {
    // Open the file in append mode to add new records without overwriting existing ones
    ofstream file("students.txt", ios::app);  
    Student s;

    // Prompt the user to enter student details
    cout << "Enter Student ID: ";
    cin >> s.id;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Marks: ";
    cin >> s.marks;

    // Write the student details to the file
    file << s.id << " " << s.name << " " << s.age << " " << s.marks << endl;
    file.close();
    cout << "Student added successfully!\n";
}

// Function to display all student records from the file
void displayStudents() {
    // Open the file for reading
    ifstream file("students.txt");
    Student s;

    cout << "\nStudent Records:\n";
    // Read each student record from the file and display it
    while (file >> s.id >> s.name >> s.age >> s.marks) {
        cout << "ID: " << s.id << ", Name: " << s.name 
             << ", Age: " << s.age << ", Marks: " << s.marks << endl;
    }

    file.close();
}

// Function to update a student's record based on their ID
void updateStudent(int searchID) {
    // Open the original file for reading and a temporary file for writing
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool found = false;

    // Read each student record from the original file
    while (file >> s.id >> s.name >> s.age >> s.marks) {
        // If the student ID matches the search ID, update the record
        if (s.id == searchID) {
            found = true;
            cout << "Enter New Name: ";
            cin >> s.name;
            cout << "Enter New Age: ";
            cin >> s.age;
            cout << "Enter New Marks: ";
            cin >> s.marks;
        }
        // Write the record (updated or not) to the temporary file
        temp << s.id << " " << s.name << " " << s.age << " " << s.marks << endl;
    }

    file.close();
    temp.close();
    // Replace the original file with the temporary file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record updated successfully!\n";
    else
        cout << "Student not found!\n";
}

// Function to delete a student's record based on their ID
void deleteStudent(int deleteID) {
    // Open the original file for reading and a temporary file for writing
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool found = false;

    // Read each student record from the original file
    while (file >> s.id >> s.name >> s.age >> s.marks) {
        // If the student ID matches the delete ID, skip writing this record to the temp file
        if (s.id == deleteID) {
            found = true;
            continue;  
        }
        // Write the record to the temporary file if it's not the one to be deleted
        temp << s.id << " " << s.name << " " << s.age << " " << s.marks << endl;
    }

    file.close();
    temp.close();
    // Replace the original file with the temporary file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice, id;
    do {
        // Display the menu options
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform the action based on the user's choice
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: 
                cout << "Enter Student ID to update: ";
                cin >> id;
                updateStudent(id);
                break;
            case 4: 
                cout << "Enter Student ID to delete: ";
                cin >> id;
                deleteStudent(id);
                break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}