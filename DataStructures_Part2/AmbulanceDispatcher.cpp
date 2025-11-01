#include "AmbulanceDispatcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>  // For sprintf_s
using namespace std;

// Global instance for the menu system
static AmbulanceDispatcher* globalDispatcher = nullptr;

// Constructor
AmbulanceDispatcher::AmbulanceDispatcher() {
    front = 0;
    rear = -1;
    count = 0;
}

// Check if queue is full
bool AmbulanceDispatcher::isFull() {
    return count == MAX_SIZE;
}

// Check if queue is empty
bool AmbulanceDispatcher::isEmpty() {
    return count == 0;
}

// Function 1: Register Ambulance (Add to circular queue)
void AmbulanceDispatcher::registerAmbulance() {
    if (isFull()) {
        cout << "\n[ERROR] Ambulance queue is full! Cannot register more ambulances.\n";
        return;
    }

    Ambulance newAmb;
    int choice;
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                          REGISTER NEW AMBULANCE                       \n";
    cout << "=======================================================================\n";
    cout << "\n";
    
    // 1. AMBULANCE ID - Auto-generate with option to customize
    cout << "1. AMBULANCE ID\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // Generate next ID based on count
    char nextID[10];
    sprintf_s(nextID, "A%03d", count + 1);
    
    cout << "Suggested ID: " << nextID << "\n";
    cout << "  1. Use suggested ID (" << nextID << ")\n";
    cout << "  2. Enter custom ID\n";
    cout << "Your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        newAmb.ambulanceID = nextID;
    } else {
        cout << "Enter Ambulance ID (format: A001, A002, etc.): ";
        cin >> newAmb.ambulanceID;
    }
    cin.ignore();
    
    // 2. DRIVER NAME - Predefined list with custom option
    cout << "\n--------------------------------------------------------------------\n";
    cout << "2. DRIVER NAME\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select driver from available staff:\n";
    cout << "  1. Amirul Hassan\n";
    cout << "  2. Siti Rahmah\n";
    cout << "  3. Daniel Chong\n";
    cout << "  4. Nurul Aina\n";
    cout << "  5. Prakash Raj\n";
    cout << "  6. Lim Wei Jian\n";
    cout << "  7. Aisyah Zahra\n";
    cout << "  8. Faizal Bahri\n";
    cout << "  9. Chong Mei Ling\n";
    cout << " 10. Haziq Danish\n";
    cout << " 11. Enter custom name\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: newAmb.driverName = "Amirul Hassan"; break;
        case 2: newAmb.driverName = "Siti Rahmah"; break;
        case 3: newAmb.driverName = "Daniel Chong"; break;
        case 4: newAmb.driverName = "Nurul Aina"; break;
        case 5: newAmb.driverName = "Prakash Raj"; break;
        case 6: newAmb.driverName = "Lim Wei Jian"; break;
        case 7: newAmb.driverName = "Aisyah Zahra"; break;
        case 8: newAmb.driverName = "Faizal Bahri"; break;
        case 9: newAmb.driverName = "Chong Mei Ling"; break;
        case 10: newAmb.driverName = "Haziq Danish"; break;
        case 11:
            cout << "Enter driver name: ";
            getline(cin, newAmb.driverName);
            break;
        default:
            newAmb.driverName = "Unknown Driver";
    }
    
    // 3. STATUS - Predefined options
    cout << "\n--------------------------------------------------------------------\n";
    cout << "3. CURRENT STATUS\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select current status:\n";
    cout << "  1. Available at Base\n";
    cout << "  2. Dispatched to Scene\n";
    cout << "  3. Transporting Patient\n";
    cout << "  4. At Hospital (Offloading)\n";
    cout << "  5. Under Maintenance\n";
    cout << "  6. Refuelling / Restocking\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: newAmb.status = "Available at Base"; break;
        case 2: newAmb.status = "Dispatched to Scene"; break;
        case 3: newAmb.status = "Transporting Patient"; break;
        case 4: newAmb.status = "At Hospital (Offloading)"; break;
        case 5: newAmb.status = "Under Maintenance"; break;
        case 6: newAmb.status = "Refuelling / Restocking"; break;
        default: newAmb.status = "Available at Base";
    }
    
    // 4. LAST DISPATCH TIME
    cout << "\n--------------------------------------------------------------------\n";
    cout << "4. LAST DISPATCH TIME\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Enter last dispatch time (format: HH:MM, e.g., 08:30): ";
    getline(cin, newAmb.lastDispatchTime);
    
    // 5. LOCATION - Predefined stations
    cout << "\n--------------------------------------------------------------------\n";
    cout << "5. CURRENT LOCATION\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select ambulance station:\n";
    cout << "  1. Hospital HQ - Emergency Wing\n";
    cout << "  2. Bandar Klang Medical Station\n";
    cout << "  3. Bukit Raja Response Unit\n";
    cout << "  4. Port Klang Substation\n";
    cout << "  5. Kapar Health Post\n";
    cout << "  6. Taman Sentosa Medical Base\n";
    cout << "  7. Enter custom location\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: newAmb.location = "Hospital HQ - Emergency Wing"; break;
        case 2: newAmb.location = "Bandar Klang Medical Station"; break;
        case 3: newAmb.location = "Bukit Raja Response Unit"; break;
        case 4: newAmb.location = "Port Klang Substation"; break;
        case 5: newAmb.location = "Kapar Health Post"; break;
        case 6: newAmb.location = "Taman Sentosa Medical Base"; break;
        case 7:
            cout << "Enter location: ";
            getline(cin, newAmb.location);
            break;
        default:
            newAmb.location = "Hospital HQ - Emergency Wing";
    }
    
    // 6. DISTANCE COVERED
    cout << "\n--------------------------------------------------------------------\n";
    cout << "6. DISTANCE COVERED\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Enter total distance covered (km): ";
    cin >> newAmb.distanceCovered;

    // Add to circular queue
    rear = (rear + 1) % MAX_SIZE;
    ambulances[rear] = newAmb;
    count++;

    cout << "\n[SUCCESS] Ambulance registered successfully!\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Ambulance ID  : " << newAmb.ambulanceID << "\n";
    cout << "  Driver        : " << newAmb.driverName << "\n";
    cout << "  Status        : " << newAmb.status << "\n";
    cout << "  Location      : " << newAmb.location << "\n";
    cout << "  Queue Position: " << count << "\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // Auto-save to CSV
    saveToCSV("Ambulance_Dispatcher_Dataset.csv");
}

// Function 2: Rotate Ambulance Shift (Circular rotation)
void AmbulanceDispatcher::rotateAmbulanceShift() {
    if (isEmpty()) {
        cout << "\n[ERROR] No ambulances in the queue to rotate.\n";
        return;
    }

    // Get the front ambulance
    Ambulance currentAmb = ambulances[front];
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                       ROTATING AMBULANCE SHIFT                         \n";
    cout << "=======================================================================\n";
    cout << "\n";
    cout << "Ambulance completing shift:\n";
    cout << "  ID: " << currentAmb.ambulanceID << "\n";
    cout << "  Driver: " << currentAmb.driverName << "\n";
    cout << "  Previous Status: " << currentAmb.status << "\n";

    // Remove from front
    front = (front + 1) % MAX_SIZE;
    count--;

    // Update status and add back to the rear (rotation)
    currentAmb.status = "Off-Duty (Resting)";
    rear = (rear + 1) % MAX_SIZE;
    ambulances[rear] = currentAmb;
    count++;

    cout << "\n[SUCCESS] Shift rotated successfully!\n";
    cout << currentAmb.ambulanceID << " moved to the back of the queue.\n";
    
    if (!isEmpty()) {
        cout << "\nNext ambulance on duty:\n";
        cout << "  ID: " << ambulances[front].ambulanceID << "\n";
        cout << "  Driver: " << ambulances[front].driverName << "\n";
        cout << "  Status: " << ambulances[front].status << "\n";
    }
    
    // Auto-save to CSV
    saveToCSV("Ambulance_Dispatcher_Dataset.csv");
}

// Function 3: Display Ambulance Schedule (Show all in rotation order)
void AmbulanceDispatcher::displayAmbulanceSchedule() {
    if (isEmpty()) {
        cout << "\n[INFO] No ambulances currently in the rotation schedule.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                      AMBULANCE ROTATION SCHEDULE                       \n";
    cout << "=======================================================================\n";
    cout << "\n";
    cout << "Total Ambulances in Queue: " << count << "\n";
    cout << "-----------------------------------------------------------------------\n";

    int index = front;
    for (int i = 0; i < count; i++) {
        if (i == 0) {
            cout << ">>> CURRENT ON-DUTY AMBULANCE <<<\n";
        } else if (i == 1) {
            cout << "\n--- NEXT IN LINE ---\n";
        } else if (i == 2) {
            cout << "\n--- STANDBY QUEUE ---\n";
        }
        
        cout << "Position " << (i + 1) << ":\n";
        cout << "  ID           : " << ambulances[index].ambulanceID << "\n";
        cout << "  Driver       : " << ambulances[index].driverName << "\n";
        cout << "  Status       : " << ambulances[index].status << "\n";
        cout << "  Last Dispatch: " << ambulances[index].lastDispatchTime << "\n";
        cout << "  Location     : " << ambulances[index].location << "\n";
        cout << "  Distance     : " << ambulances[index].distanceCovered << " km\n";
        cout << "-----------------------------------------------------------------------\n";
        
        index = (index + 1) % MAX_SIZE;
    }
    cout << "\n";
}

// Load data from CSV file
void AmbulanceDispatcher::loadFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not open " << filename << "\n";
        cout << "Please ensure the file exists in the same directory.\n";
        return;
    }

    // Clear existing data before loading
    front = 0;
    rear = -1;
    count = 0;

    string line;
    getline(file, line); // Skip header line

    int loadedCount = 0;
    while (getline(file, line) && !isFull()) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Ambulance amb;
        
        getline(ss, amb.ambulanceID, ',');
        getline(ss, amb.driverName, ',');
        getline(ss, amb.status, ',');
        getline(ss, amb.lastDispatchTime, ',');
        
        // Skip next shift field (rotation order)
        string temp;
        getline(ss, temp, ',');
        
        getline(ss, amb.location, ',');
        string distStr;
        getline(ss, distStr);
        
        // Parse distance (handle potential formatting issues)
        try {
            amb.distanceCovered = stoi(distStr);
        } catch (...) {
            amb.distanceCovered = 0;
        }

        // Add to circular queue
        rear = (rear + 1) % MAX_SIZE;
        ambulances[rear] = amb;
        count++;
        loadedCount++;
    }

    file.close();
    cout << "\n[SUCCESS] Loaded " << loadedCount << " ambulances from " << filename << "\n";
}

// Save data to CSV file
void AmbulanceDispatcher::saveToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not create/open " << filename << " for writing.\n";
        return;
    }

    // Write CSV header
    file << "Ambulance ID,Driver Name,Status,Last Dispatch Time,Next Shift (Rotation Order),Location (Current Station),Distance Covered (km)\n";

    // Write all ambulances in queue order
    int index = front;
    for (int i = 0; i < count; i++) {
        file << ambulances[index].ambulanceID << ","
             << ambulances[index].driverName << ","
             << ambulances[index].status << ","
             << ambulances[index].lastDispatchTime << ","
             << (i + 1) << ","
             << ambulances[index].location << ","
             << ambulances[index].distanceCovered << "\n";
        
        index = (index + 1) % MAX_SIZE;
    }

    file.close();
    cout << "\n[SUCCESS] Saved " << count << " ambulances to " << filename << "\n";
}

// Get count of ambulances
int AmbulanceDispatcher::getCount() {
    return count;
}

// Menu function for Ambulance Dispatcher module
void ambulanceDispatcherMenu() {
    // Create dispatcher instance if not exists
    if (globalDispatcher == nullptr) {
        globalDispatcher = new AmbulanceDispatcher();
        // Auto-load data from CSV on first entry
        globalDispatcher->loadFromCSV("Ambulance_Dispatcher_Dataset.csv");
    }
    
    int choice;
    
    do {
        cout << "\n";
        cout << "=======================================================================\n";
        cout << "                      AMBULANCE DISPATCHER MANAGEMENT                 \n";
        cout << "                         (Circular Queue System)                       \n";
        cout << "=======================================================================\n";
        cout << "\nOPTIONS:\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "  1. Register Ambulance\n";
        cout << "  2. Rotate Ambulance Shift\n";
        cout << "  3. Display Ambulance Schedule\n";
        cout << "  4. Load Data from CSV (Reload)\n";
        cout << "  5. Save Data to CSV\n";
        cout << "  0. Return to Main Menu\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                globalDispatcher->registerAmbulance();
                break;
            case 2:
                globalDispatcher->rotateAmbulanceShift();
                break;
            case 3:
                globalDispatcher->displayAmbulanceSchedule();
                break;
            case 4:
                globalDispatcher->loadFromCSV("Ambulance_Dispatcher_Dataset.csv");
                break;
            case 5:
                globalDispatcher->saveToCSV("Ambulance_Dispatcher_Dataset.csv");
                break;
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please enter a number between 0-5.\n";
        }
        
        // Pause before showing menu again (except when exiting)
        if (choice != 0 && choice >= 1 && choice <= 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
}

