// DataStructures_Part2.cpp : Hospital Patient Care Management System
// Main program file with integrated menu system
// Team Project - Data Structures Part 2

#include <iostream>
#include "AmbulanceDispatcher.h"
#include "MedicalSupplyManager.h"

using namespace std;

// Function prototypes for other modules (to be implemented by other team members)
void patientAdmissionClerkMenu();
void emergencyDepartmentOfficerMenu();

// Display main menu header
void displayMainMenuHeader() {
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                   HOSPITAL PATIENT CARE MANAGEMENT SYSTEM            \n";
    cout << "                         Using Core Data Structures                    \n";
    cout << "=======================================================================\n";
}

// Main function
int main() {
    int mainChoice;
    
    // Display welcome message
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "             Welcome to Hospital Patient Care Management System!       \n";
    cout << "                   Peak Operations Management Solution                \n";
    cout << "=======================================================================\n";
    
    do {
        displayMainMenuHeader();
        cout << "\nSELECT MODULE:\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "  1. Patient Admission Clerk\n";
        cout << "     - Manage patient queue and admissions\n";
        cout << "\n";
        cout << "  2. Medical Supply Manager\n";
        cout << "     - Track and manage medical supplies\n";
        cout << "\n";
        cout << "  3. Emergency Department Officer\n";
        cout << "     - Handle emergency cases by priority\n";
        cout << "\n";
        cout << "  4. Ambulance Dispatcher\n";
        cout << "     - Schedule ambulance rotations\n";
        cout << "\n";
        cout << "  0. Exit System\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "\nEnter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                cout << "\n[INFO] Patient Admission Clerk module\n";
                cout << "This module will be implemented by team member 1.\n";
                cout << "Expected features:\n";
                cout << "  - Admit Patient\n";
                cout << "  - Discharge Patient\n";
                cout << "  - View Patient Queue\n";
                cout << "\nPress Enter to return to main menu...";
                cin.ignore();
                cin.get();
                // patientAdmissionClerkMenu(); // Uncomment when implemented
                break;
                
            case 2:
                // Medical Supply Manager - MODULE 2 (Implemented)
                medicalSupplyManagerMenu();
                break;
                
            case 3:
                cout << "\n[INFO] Emergency Department Officer module\n";
                cout << "This module will be implemented by team member 3.\n";
                cout << "Expected features:\n";
                cout << "  - Log Emergency Case\n";
                cout << "  - Process Most Critical Case\n";
                cout << "  - View Pending Emergency Cases\n";
                cout << "\nPress Enter to return to main menu...";
                cin.ignore();
                cin.get();
                // emergencyDepartmentOfficerMenu(); // Uncomment when implemented
                break;
                
            case 4:
                // Ambulance Dispatcher - YOUR MODULE (Implemented)
                ambulanceDispatcherMenu();
                break;
                
            case 0:
                cout << "\n";
                cout << "=======================================================================\n";
                cout << "          Thank you for using the Hospital Management System!          \n";
                cout << "                      Stay safe and healthy!                           \n";
                cout << "=======================================================================\n";
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please enter a number between 0-4.\n";
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
        }
    } while (mainChoice != 0);

    return 0;
}

// Placeholder function implementations (for future integration)
// These will be replaced by actual implementations from other team members

void patientAdmissionClerkMenu() {
    // To be implemented by team member handling Patient Admission Clerk role
    // Recommended data structure: Queue (FIFO)
}

// medicalSupplyManagerMenu() is now implemented in MedicalSupplyManager.cpp

void emergencyDepartmentOfficerMenu() {
    // To be implemented by team member handling Emergency Department Officer role
    // Recommended data structure: Priority Queue (based on severity)
}
