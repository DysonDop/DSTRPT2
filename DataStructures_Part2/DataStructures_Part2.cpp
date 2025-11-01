// DataStructures_Part2.cpp : Hospital Patient Care Management System
// Main program file with integrated menu system
// Team Project - Data Structures Part 2

#include <iostream>
#include "AmbulanceDispatcher.h"
#include "MedicalSupplyManager.h"
#include "EDO.h"
#include "PAC.h"

using namespace std;

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
                // Patient Admission Clerk - MODULE 1 (Implemented)
                patientAdmissionClerkMenu();
                break;
                
            case 2:
                // Medical Supply Manager - MODULE 2 (Implemented)
                medicalSupplyManagerMenu();
                break;
                
            case 3:
                // Emergency Department Officer - MODULE 3 (Implemented)
                emergencyDepartmentOfficerMenu();
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

// Module implementations:
// patientAdmissionClerkMenu() is now implemented in PAC.cpp
// medicalSupplyManagerMenu() is now implemented in MedicalSupplyManager.cpp
// emergencyDepartmentOfficerMenu() is now implemented in EDO.cpp
// ambulanceDispatcherMenu() is now implemented in AmbulanceDispatcher.cpp
