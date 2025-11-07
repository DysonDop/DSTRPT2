#include "AmbulanceDispatcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;

// Global instance for the menu system
static AmbulanceDispatcher* globalDispatcher = nullptr;

// Constants
const int INPUT_BUFFER_CLEAR_SIZE = 10000;
const string AMBULANCE_CSV_FILENAME = "Ambulance_Dispatcher_Dataset.csv";

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
    stringstream ss;
    ss << "A" << setfill('0') << setw(3) << (count + 1);
    string nextID = ss.str();
    
    cout << "Suggested ID: " << nextID << "\n";
    cout << "  1. Use suggested ID (" << nextID << ")\n";
    cout << "  2. Enter custom ID\n";
    cout << "Your choice: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Using suggested ID: " << nextID << "\n";
        newAmb.ambulanceID = nextID;
    } else if (choice == 1) {
        newAmb.ambulanceID = nextID;
    } else if (choice == 2) {
        cout << "Enter Ambulance ID (format: A001, A002, etc.): ";
        cin >> newAmb.ambulanceID;
        if (newAmb.ambulanceID.empty()) {
            cout << "\n[WARNING] ID cannot be empty! Using suggested ID: " << nextID << "\n";
            newAmb.ambulanceID = nextID;
        }
    } else {
        cout << "\n[WARNING] Invalid choice! Using suggested ID: " << nextID << "\n";
        newAmb.ambulanceID = nextID;
    }
    cin.ignore();
    
    // 2. DRIVER NAME - Predefined list with custom option
    cout << "\n2. DRIVER NAME\n";
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
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Driver name set to 'Unknown Driver'.\n";
        newAmb.driverName = "Unknown Driver";
    } else {
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
                if (newAmb.driverName.empty()) {
                    cout << "\n[WARNING] Driver name cannot be empty! Set to 'Unknown Driver'.\n";
                    newAmb.driverName = "Unknown Driver";
                }
                break;
            default:
                cout << "\n[WARNING] Invalid choice! Driver name set to 'Unknown Driver'.\n";
                newAmb.driverName = "Unknown Driver";
        }
    }
    
    // 3. STATUS - Predefined options
    cout << "\n3. CURRENT STATUS\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Select current status:\n";
    cout << "  1. Available at Base\n";
    cout << "  2. Dispatched to Scene\n";
    cout << "  3. Transporting Patient\n";
    cout << "  4. At Hospital (Offloading)\n";
    cout << "  5. Under Maintenance\n";
    cout << "  6. Refuelling / Restocking\n";
    cout << "Your choice: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Status set to 'Available at Base'.\n";
        newAmb.status = "Available at Base";
    } else {
        cin.ignore();
        
        switch (choice) {
            case 1: newAmb.status = "Available at Base"; break;
            case 2: newAmb.status = "Dispatched to Scene"; break;
            case 3: newAmb.status = "Transporting Patient"; break;
            case 4: newAmb.status = "At Hospital (Offloading)"; break;
            case 5: newAmb.status = "Under Maintenance"; break;
            case 6: newAmb.status = "Refuelling / Restocking"; break;
            default: 
                cout << "\n[WARNING] Invalid choice! Status set to 'Available at Base'.\n";
                newAmb.status = "Available at Base";
        }
    }
    
    // 4. LAST DISPATCH TIME
    cout << "\n4. LAST DISPATCH TIME\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Enter last dispatch time (format: HH:MM, e.g., 08:30): ";
    getline(cin, newAmb.lastDispatchTime);
    
    // 5. LOCATION - Predefined stations
    cout << "\n5. CURRENT LOCATION\n";
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
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Location set to default: Hospital HQ - Emergency Wing\n";
        newAmb.location = "Hospital HQ - Emergency Wing";
    } else {
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
                if (newAmb.location.empty()) {
                    cout << "\n[WARNING] Location cannot be empty! Set to default.\n";
                    newAmb.location = "Hospital HQ - Emergency Wing";
                }
                break;
            default:
                cout << "\n[WARNING] Invalid choice! Location set to default.\n";
                newAmb.location = "Hospital HQ - Emergency Wing";
        }
    }
    
    // 6. DISTANCE COVERED
    cout << "\n6. DISTANCE COVERED\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Enter total distance covered (km): ";
    if (!(cin >> newAmb.distanceCovered)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Distance set to 0.\n";
        newAmb.distanceCovered = 0;
    } else if (newAmb.distanceCovered < 0) {
        cout << "\n[WARNING] Distance cannot be negative! Distance set to 0.\n";
        newAmb.distanceCovered = 0;
    }

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
    saveToCSV(AMBULANCE_CSV_FILENAME);
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
    saveToCSV(AMBULANCE_CSV_FILENAME);
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

// Function 4: Find Ambulance Index by ID (returns -1 if not found)
int AmbulanceDispatcher::findAmbulanceIndexByID(string id) {
    int index = front;
    for (int i = 0; i < count; i++) {
        if (ambulances[index].ambulanceID == id) {
            return index;
        }
        index = (index + 1) % MAX_SIZE;
    }
    return -1; // Not found
}

// Function 4: Find Ambulance Index by Driver Name (returns -1 if not found)
int AmbulanceDispatcher::findAmbulanceIndexByDriver(string driverName) {
    int index = front;
    for (int i = 0; i < count; i++) {
        if (ambulances[index].driverName == driverName) {
            return index;
        }
        index = (index + 1) % MAX_SIZE;
    }
    return -1; // Not found
}

// Function 4: Search Ambulance (by ID or Driver Name)
void AmbulanceDispatcher::searchAmbulance() {
    if (isEmpty()) {
        cout << "\n[ERROR] No ambulances in the queue to search.\n";
        return;
    }

    int choice;
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                          SEARCH AMBULANCE                             \n";
    cout << "=======================================================================\n";
    cout << "\nSearch by:\n";
    cout << "  1. Ambulance ID\n";
    cout << "  2. Driver Name\n";
    cout << "  0. Cancel\n";
    cout << "Your choice: ";
    
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Please enter a number.\n";
        return;
    }
    cin.ignore();

    if (choice == 0) {
        cout << "\n[CANCELLED] Search cancelled.\n";
        return;
    }

    int foundIndex = -1;

    if (choice == 1) {
        cout << "\nAvailable Ambulance IDs:\n";
        cout << "-----------------------------------------------------------------------\n";
        int index = front;
        int optionNum = 1;
        int indices[MAX_SIZE];
        
        for (int i = 0; i < count; i++) {
            indices[optionNum - 1] = index;
            cout << "  " << optionNum << ". " << ambulances[index].ambulanceID 
                 << " - " << ambulances[index].driverName << "\n";
            optionNum++;
            index = (index + 1) % MAX_SIZE;
        }
        cout << "  0. Cancel\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Select Ambulance ID: ";
        
        int idChoice;
        if (!(cin >> idChoice)) {
            cin.clear();
            cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            return;
        }
        cin.ignore();
        
        if (idChoice == 0) {
            cout << "\n[CANCELLED] Search cancelled.\n";
            return;
        }
        
        if (idChoice < 1 || idChoice > count) {
            cout << "\n[ERROR] Invalid choice! Please select a number between 1-" << count << ".\n";
            return;
        }
        
        foundIndex = indices[idChoice - 1];
        
    } else if (choice == 2) {
        cout << "\nAvailable Drivers:\n";
        cout << "-----------------------------------------------------------------------\n";
        int index = front;
        int optionNum = 1;
        string drivers[MAX_SIZE];
        int indices[MAX_SIZE];
        int driverCount = 0;
        
        for (int i = 0; i < count; i++) {
            bool found = false;
            for (int j = 0; j < driverCount; j++) {
                if (drivers[j] == ambulances[index].driverName) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                drivers[driverCount] = ambulances[index].driverName;
                indices[driverCount] = index;
                cout << "  " << (driverCount + 1) << ". " << ambulances[index].driverName 
                     << " (" << ambulances[index].ambulanceID << ")\n";
                driverCount++;
            }
            index = (index + 1) % MAX_SIZE;
        }
        cout << "  0. Cancel\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Select Driver: ";
        
        int driverChoice;
        if (!(cin >> driverChoice)) {
            cin.clear();
            cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            return;
        }
        cin.ignore();
        
        if (driverChoice == 0) {
            cout << "\n[CANCELLED] Search cancelled.\n";
            return;
        }
        
        if (driverChoice < 1 || driverChoice > driverCount) {
            cout << "\n[ERROR] Invalid choice! Please select a number between 1-" << driverCount << ".\n";
            return;
        }
        
        foundIndex = indices[driverChoice - 1];
        
    } else {
        cout << "\n[ERROR] Invalid choice! Please select 1, 2, or 0.\n";
        return;
    }

    if (foundIndex == -1) {
        cout << "\n[ERROR] Ambulance not found in the queue.\n";
        return;
    }

    cout << "\n[SUCCESS] Ambulance found!\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Ambulance ID  : " << ambulances[foundIndex].ambulanceID << "\n";
    cout << "  Driver        : " << ambulances[foundIndex].driverName << "\n";
    cout << "  Status        : " << ambulances[foundIndex].status << "\n";
    cout << "  Last Dispatch : " << ambulances[foundIndex].lastDispatchTime << "\n";
    cout << "  Location      : " << ambulances[foundIndex].location << "\n";
    cout << "  Distance      : " << ambulances[foundIndex].distanceCovered << " km\n";
    
    int position = 0;
    int tempIndex = front;
    while (tempIndex != foundIndex && position < count) {
        position++;
        tempIndex = (tempIndex + 1) % MAX_SIZE;
    }
    cout << "  Queue Position: " << (position + 1) << "\n";
    cout << "-----------------------------------------------------------------------\n";
}

// Function 5: Update Ambulance Status
bool AmbulanceDispatcher::updateAmbulanceStatus(string id, string newStatus) {
    int index = findAmbulanceIndexByID(id);
    if (index == -1) {
        return false;
    }
    ambulances[index].status = newStatus;
    return true;
}

// Function 5: Update Ambulance Details
void AmbulanceDispatcher::updateAmbulanceDetails() {
    if (isEmpty()) {
        cout << "\n[ERROR] No ambulances in the queue to update.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                       UPDATE AMBULANCE DETAILS                        \n";
    cout << "=======================================================================\n";
    
    cout << "\nSelect Ambulance to Update:\n";
    cout << "-----------------------------------------------------------------------\n";
    int tempIndex = front;
    int optionNum = 1;
    int indices[MAX_SIZE];
    
    for (int i = 0; i < count; i++) {
        indices[optionNum - 1] = tempIndex;
        cout << "  " << optionNum << ". " << ambulances[tempIndex].ambulanceID 
             << " - " << ambulances[tempIndex].driverName 
             << " (" << ambulances[tempIndex].status << ")\n";
        optionNum++;
        tempIndex = (tempIndex + 1) % MAX_SIZE;
    }
    cout << "  0. Cancel\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your choice: ";
    
    int idChoice;
    if (!(cin >> idChoice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Please enter a number.\n";
        return;
    }
    cin.ignore();
    
    if (idChoice == 0) {
        cout << "\n[CANCELLED] Update cancelled.\n";
        return;
    }
    
    if (idChoice < 1 || idChoice > count) {
        cout << "\n[ERROR] Invalid choice! Please select a number between 1-" << count << ".\n";
        return;
    }
    
    int index = indices[idChoice - 1];

    cout << "\nCurrent Details:\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Ambulance ID  : " << ambulances[index].ambulanceID << "\n";
    cout << "  Driver        : " << ambulances[index].driverName << "\n";
    cout << "  Status        : " << ambulances[index].status << "\n";
    cout << "  Last Dispatch : " << ambulances[index].lastDispatchTime << "\n";
    cout << "  Location      : " << ambulances[index].location << "\n";
    cout << "  Distance      : " << ambulances[index].distanceCovered << " km\n";
    cout << "-----------------------------------------------------------------------\n";

    int choice;
    cout << "\nWhat would you like to update?\n";
    cout << "  1. Status\n";
    cout << "  2. Last Dispatch Time\n";
    cout << "  3. Location\n";
    cout << "  4. Distance Covered\n";
    cout << "  5. Driver Name\n";
    cout << "  0. Cancel\n";
    cout << "Your choice: ";
    
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Please enter a number.\n";
        return;
    }
    cin.ignore();

    switch (choice) {
        case 1: {
            cout << "\nSelect new status:\n";
            cout << "  1. Available at Base\n";
            cout << "  2. Dispatched to Scene\n";
            cout << "  3. Transporting Patient\n";
            cout << "  4. At Hospital (Offloading)\n";
            cout << "  5. Under Maintenance\n";
            cout << "  6. Refuelling / Restocking\n";
            cout << "Your choice: ";
            int statusChoice;
            if (!(cin >> statusChoice)) {
                cin.clear();
                cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
                cout << "\n[ERROR] Invalid input! Please enter a number.\n";
                return;
            }
            cin.ignore();
            switch (statusChoice) {
                case 1: ambulances[index].status = "Available at Base"; break;
                case 2: ambulances[index].status = "Dispatched to Scene"; break;
                case 3: ambulances[index].status = "Transporting Patient"; break;
                case 4: ambulances[index].status = "At Hospital (Offloading)"; break;
                case 5: ambulances[index].status = "Under Maintenance"; break;
                case 6: ambulances[index].status = "Refuelling / Restocking"; break;
                default: 
                    cout << "\n[ERROR] Invalid status choice! Please select 1-6.\n";
                    return;
            }
            break;
        }
        case 2: {
            cout << "\nEnter new last dispatch time (format: HH:MM, e.g., 14:30): ";
            string timeInput;
            getline(cin, timeInput);
            
            if (timeInput.length() == 5 && timeInput[2] == ':' &&
                isdigit(timeInput[0]) && isdigit(timeInput[1]) &&
                isdigit(timeInput[3]) && isdigit(timeInput[4])) {
                int hour = stoi(timeInput.substr(0, 2));
                int minute = stoi(timeInput.substr(3, 2));
                if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
                    ambulances[index].lastDispatchTime = timeInput;
                } else {
                    cout << "\n[WARNING] Invalid time! Hours must be 0-23, minutes must be 0-59.\n";
                    cout << "Time not updated. Please try again.\n";
                    return;
                }
            } else {
                cout << "\n[WARNING] Invalid time format! Expected HH:MM (e.g., 14:30).\n";
                cout << "Time not updated. Please try again.\n";
                return;
            }
            break;
        }
        case 3: {
            cout << "\nSelect new location:\n";
            cout << "  1. Hospital HQ - Emergency Wing\n";
            cout << "  2. Bandar Klang Medical Station\n";
            cout << "  3. Bukit Raja Response Unit\n";
            cout << "  4. Port Klang Substation\n";
            cout << "  5. Kapar Health Post\n";
            cout << "  6. Taman Sentosa Medical Base\n";
            cout << "  7. Enter custom location\n";
            cout << "Your choice: ";
            int locChoice;
            if (!(cin >> locChoice)) {
                cin.clear();
                cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
                cout << "\n[ERROR] Invalid input! Please enter a number.\n";
                return;
            }
            cin.ignore();
            switch (locChoice) {
                case 1: ambulances[index].location = "Hospital HQ - Emergency Wing"; break;
                case 2: ambulances[index].location = "Bandar Klang Medical Station"; break;
                case 3: ambulances[index].location = "Bukit Raja Response Unit"; break;
                case 4: ambulances[index].location = "Port Klang Substation"; break;
                case 5: ambulances[index].location = "Kapar Health Post"; break;
                case 6: ambulances[index].location = "Taman Sentosa Medical Base"; break;
                case 7:
                    cout << "Enter custom location: ";
                    getline(cin, ambulances[index].location);
                    if (ambulances[index].location.empty()) {
                        cout << "\n[WARNING] Location cannot be empty! Location not updated.\n";
                        return;
                    }
                    break;
                default: 
                    cout << "\n[ERROR] Invalid location choice! Please select 1-7.\n";
                    return;
            }
            break;
        }
        case 4: {
            cout << "\nEnter new distance covered (km): ";
            int distance;
            if (!(cin >> distance)) {
                cin.clear();
                cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
                cout << "\n[ERROR] Invalid input! Please enter a valid number.\n";
                return;
            }
            cin.ignore();
            
            if (distance < 0) {
                cout << "\n[ERROR] Distance cannot be negative! Distance not updated.\n";
                return;
            }
            
            ambulances[index].distanceCovered = distance;
            break;
        }
        case 5:
            cout << "\nEnter new driver name: ";
            getline(cin, ambulances[index].driverName);
            break;
        case 0:
            cout << "\n[CANCELLED] Update cancelled.\n";
            return;
        default:
            cout << "\n[ERROR] Invalid choice!\n";
            return;
    }

    cout << "\n[SUCCESS] Ambulance details updated successfully!\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Ambulance ID  : " << ambulances[index].ambulanceID << "\n";
    cout << "  Driver        : " << ambulances[index].driverName << "\n";
    cout << "  Status        : " << ambulances[index].status << "\n";
    cout << "  Last Dispatch : " << ambulances[index].lastDispatchTime << "\n";
    cout << "  Location      : " << ambulances[index].location << "\n";
    cout << "  Distance      : " << ambulances[index].distanceCovered << " km\n";
    cout << "-----------------------------------------------------------------------\n";
    
    saveToCSV(AMBULANCE_CSV_FILENAME);
}

// Function 6: Remove Ambulance by ID
bool AmbulanceDispatcher::removeAmbulanceByID(string id) {
    int index = findAmbulanceIndexByID(id);
    if (index == -1) {
        return false;
    }

    if (count == 1) {
        front = 0;
        rear = -1;
        count = 0;
        return true;
    }

    if (index == front) {
        front = (front + 1) % MAX_SIZE;
        count--;
        return true;
    }

    if (index == rear) {
        if (rear == 0) {
            rear = MAX_SIZE - 1;
        } else {
            rear--;
        }
        count--;
        return true;
    }

    int current = index;
    int next = (current + 1) % MAX_SIZE;
    
    while (next != ((rear + 1) % MAX_SIZE)) {
        ambulances[current] = ambulances[next];
        current = next;
        next = (next + 1) % MAX_SIZE;
    }
    
    if (rear == 0) {
        rear = MAX_SIZE - 1;
    } else {
        rear--;
    }
    count--;
    
    return true;
}

// Function 6: Remove Ambulance from Queue
void AmbulanceDispatcher::removeAmbulanceFromQueue() {
    if (isEmpty()) {
        cout << "\n[ERROR] No ambulances in the queue to remove.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                      REMOVE AMBULANCE FROM QUEUE                      \n";
    cout << "=======================================================================\n";
    
    cout << "\nSelect Ambulance to Remove:\n";
    cout << "-----------------------------------------------------------------------\n";
    int tempIndex = front;
    int optionNum = 1;
    int indices[MAX_SIZE];
    
    for (int i = 0; i < count; i++) {
        indices[optionNum - 1] = tempIndex;
        cout << "  " << optionNum << ". " << ambulances[tempIndex].ambulanceID 
             << " - " << ambulances[tempIndex].driverName 
             << " (" << ambulances[tempIndex].status << ")\n";
        optionNum++;
        tempIndex = (tempIndex + 1) % MAX_SIZE;
    }
    cout << "  0. Cancel\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your choice: ";
    
    int idChoice;
    if (!(cin >> idChoice)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Please enter a number.\n";
        return;
    }
    cin.ignore();
    
    if (idChoice == 0) {
        cout << "\n[CANCELLED] Removal cancelled.\n";
        return;
    }
    
    if (idChoice < 1 || idChoice > count) {
        cout << "\n[ERROR] Invalid choice! Please select a number between 1-" << count << ".\n";
        return;
    }
    
    int index = indices[idChoice - 1];
    string id = ambulances[index].ambulanceID;

    cout << "\nAmbulance to be removed:\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Ambulance ID  : " << ambulances[index].ambulanceID << "\n";
    cout << "  Driver        : " << ambulances[index].driverName << "\n";
    cout << "  Status        : " << ambulances[index].status << "\n";
    cout << "-----------------------------------------------------------------------\n";

    char confirm;
    cout << "\nAre you sure you want to remove this ambulance? (Y/N): ";
    if (!(cin >> confirm)) {
        cin.clear();
        cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
        cout << "\n[ERROR] Invalid input! Removal cancelled.\n";
        return;
    }
    cin.ignore();

    if (confirm == 'Y' || confirm == 'y') {
        if (removeAmbulanceByID(id)) {
            cout << "\n[SUCCESS] Ambulance removed from queue successfully!\n";
            cout << "Remaining ambulances in queue: " << count << "\n";
            
            saveToCSV(AMBULANCE_CSV_FILENAME);
        } else {
            cout << "\n[ERROR] Failed to remove ambulance.\n";
        }
    } else {
        cout << "\n[CANCELLED] Removal cancelled.\n";
    }
}

// Function 7: Get Total Distance Covered
int AmbulanceDispatcher::getTotalDistanceCovered() {
    int total = 0;
    int index = front;
    for (int i = 0; i < count; i++) {
        total += ambulances[index].distanceCovered;
        index = (index + 1) % MAX_SIZE;
    }
    return total;
}

// Function 7: Get Average Distance
double AmbulanceDispatcher::getAverageDistance() {
    if (count == 0) return 0.0;
    return (double)getTotalDistanceCovered() / count;
}

// Function 7: Get Available Count
int AmbulanceDispatcher::getAvailableCount() {
    int available = 0;
    int index = front;
    for (int i = 0; i < count; i++) {
        if (ambulances[index].status == "Available at Base") {
            available++;
        }
        index = (index + 1) % MAX_SIZE;
    }
    return available;
}

// Function 7: Get Busy Count
int AmbulanceDispatcher::getBusyCount() {
    int busy = 0;
    int index = front;
    for (int i = 0; i < count; i++) {
        if (ambulances[index].status == "Dispatched to Scene" || 
            ambulances[index].status == "Transporting Patient" ||
            ambulances[index].status == "At Hospital (Offloading)") {
            busy++;
        }
        index = (index + 1) % MAX_SIZE;
    }
    return busy;
}

// Function 7: Display Queue Statistics
void AmbulanceDispatcher::displayQueueStatistics() {
    if (isEmpty()) {
        cout << "\n[INFO] No ambulances in the queue.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                        QUEUE STATISTICS                               \n";
    cout << "=======================================================================\n";
    cout << "\n";
    
    int totalDistance = getTotalDistanceCovered();
    double avgDistance = getAverageDistance();
    int available = getAvailableCount();
    int busy = getBusyCount();
    int maintenance = 0;
    int refuelling = 0;
    
    int index = front;
    for (int i = 0; i < count; i++) {
        if (ambulances[index].status == "Under Maintenance") {
            maintenance++;
        } else if (ambulances[index].status == "Refuelling / Restocking") {
            refuelling++;
        }
        index = (index + 1) % MAX_SIZE;
    }

    cout << "OVERVIEW:\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Total Ambulances      : " << count << "\n";
    cout << "  Available at Base     : " << available << "\n";
    cout << "  Currently Busy        : " << busy << "\n";
    cout << "  Under Maintenance     : " << maintenance << "\n";
    cout << "  Refuelling/Restocking : " << refuelling << "\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "\nDISTANCE STATISTICS:\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Total Distance Covered : " << totalDistance << " km\n";
    cout << "  Average Distance       : " << fixed << setprecision(2) << avgDistance << " km\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "\nQUEUE UTILIZATION:\n";
    cout << "-----------------------------------------------------------------------\n";
    double utilization = (count > 0) ? ((double)busy / count * 100.0) : 0.0;
    cout << "  Active Utilization    : " << fixed << setprecision(1) << utilization << "%\n";
    cout << "  Queue Capacity        : " << MAX_SIZE << " (Max)\n";
    cout << "  Current Usage         : " << count << " / " << MAX_SIZE << "\n";
    cout << "-----------------------------------------------------------------------\n";
}

// Function 8: Display by Status
void AmbulanceDispatcher::displayByStatus(string status) {
    if (isEmpty()) {
        cout << "\n[INFO] No ambulances in the queue.\n";
        return;
    }

    int found = 0;
    int index = front;
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "              AMBULANCES WITH STATUS: " << status << "\n";
    cout << "=======================================================================\n";
    cout << "\n";

    for (int i = 0; i < count; i++) {
        if (ambulances[index].status == status) {
            found++;
            cout << "Ambulance " << found << ":\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "  Ambulance ID  : " << ambulances[index].ambulanceID << "\n";
            cout << "  Driver        : " << ambulances[index].driverName << "\n";
            cout << "  Status        : " << ambulances[index].status << "\n";
            cout << "  Last Dispatch : " << ambulances[index].lastDispatchTime << "\n";
            cout << "  Location      : " << ambulances[index].location << "\n";
            cout << "  Distance      : " << ambulances[index].distanceCovered << " km\n";
            cout << "-----------------------------------------------------------------------\n";
        }
        index = (index + 1) % MAX_SIZE;
    }

    if (found == 0) {
        cout << "[INFO] No ambulances found with status: " << status << "\n";
    } else {
        cout << "\nTotal found: " << found << " ambulance(s)\n";
    }
}

// Function 8: Display by Location
void AmbulanceDispatcher::displayByLocation(string location) {
    if (isEmpty()) {
        cout << "\n[INFO] No ambulances in the queue.\n";
        return;
    }

    int found = 0;
    int index = front;
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "              AMBULANCES AT LOCATION: " << location << "\n";
    cout << "=======================================================================\n";
    cout << "\n";

    for (int i = 0; i < count; i++) {
        if (ambulances[index].location == location) {
            found++;
            cout << "Ambulance " << found << ":\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "  Ambulance ID  : " << ambulances[index].ambulanceID << "\n";
            cout << "  Driver        : " << ambulances[index].driverName << "\n";
            cout << "  Status        : " << ambulances[index].status << "\n";
            cout << "  Last Dispatch : " << ambulances[index].lastDispatchTime << "\n";
            cout << "  Location      : " << ambulances[index].location << "\n";
            cout << "  Distance      : " << ambulances[index].distanceCovered << " km\n";
            cout << "-----------------------------------------------------------------------\n";
        }
        index = (index + 1) % MAX_SIZE;
    }

    if (found == 0) {
        cout << "[INFO] No ambulances found at location: " << location << "\n";
    } else {
        cout << "\nTotal found: " << found << " ambulance(s)\n";
    }
}

// Function 8: Display Available Ambulances
void AmbulanceDispatcher::displayAvailableAmbulances() {
    displayByStatus("Available at Base");
}

// Menu function for Ambulance Dispatcher module
void ambulanceDispatcherMenu() {
    // Create dispatcher instance if not exists
    if (globalDispatcher == nullptr) {
        globalDispatcher = new AmbulanceDispatcher();
        // Auto-load data from CSV on first entry
        globalDispatcher->loadFromCSV(AMBULANCE_CSV_FILENAME);
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
        cout << "QUEUE OPERATIONS:\n";
        cout << "  1. Register Ambulance\n";
        cout << "  2. Rotate Ambulance Shift\n";
        cout << "  3. Display Ambulance Schedule\n";
        cout << "\nAMBULANCE MANAGEMENT:\n";
        cout << "  4. Search Ambulance\n";
        cout << "  5. Update Ambulance Details\n";
        cout << "  6. Remove Ambulance from Queue\n";
        cout << "\nREPORTS & ANALYTICS:\n";
        cout << "  7. Display Queue Statistics\n";
        cout << "  8. Filter Display Options\n";
        cout << "\nDATA MANAGEMENT:\n";
        cout << "  9. Load Data from CSV (Reload)\n";
        cout << " 10. Save Data to CSV\n";
        cout << "\n  0. Return to Main Menu\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            cout << "\nPress Enter to continue...";
            cin.get();
            continue;
        }

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
                globalDispatcher->searchAmbulance();
                break;
            case 5:
                globalDispatcher->updateAmbulanceDetails();
                break;
            case 6:
                globalDispatcher->removeAmbulanceFromQueue();
                break;
            case 7:
                globalDispatcher->displayQueueStatistics();
                break;
            case 8: {
                int filterChoice;
                cout << "\n";
                cout << "=======================================================================\n";
                cout << "                        FILTER DISPLAY OPTIONS                        \n";
                cout << "=======================================================================\n";
                cout << "\nFilter by:\n";
                cout << "  1. Status (Available at Base)\n";
                cout << "  2. Status (Dispatched to Scene)\n";
                cout << "  3. Status (Transporting Patient)\n";
                cout << "  4. Status (At Hospital - Offloading)\n";
                cout << "  5. Status (Under Maintenance)\n";
                cout << "  6. Status (Refuelling / Restocking)\n";
                cout << "  7. Location (Hospital HQ - Emergency Wing)\n";
                cout << "  8. Location (Bandar Klang Medical Station)\n";
                cout << "  9. Location (Bukit Raja Response Unit)\n";
                cout << " 10. Location (Port Klang Substation)\n";
                cout << " 11. Location (Kapar Health Post)\n";
                cout << " 12. Location (Taman Sentosa Medical Base)\n";
                cout << "  0. Cancel\n";
                cout << "Your choice: ";
                if (!(cin >> filterChoice)) {
                    cin.clear();
                    cin.ignore(INPUT_BUFFER_CLEAR_SIZE, '\n');
                    cout << "\n[ERROR] Invalid input! Please enter a number.\n";
                    filterChoice = 0;
                }
                cin.ignore();
                
                switch (filterChoice) {
                    case 1:
                        globalDispatcher->displayByStatus("Available at Base");
                        break;
                    case 2:
                        globalDispatcher->displayByStatus("Dispatched to Scene");
                        break;
                    case 3:
                        globalDispatcher->displayByStatus("Transporting Patient");
                        break;
                    case 4:
                        globalDispatcher->displayByStatus("At Hospital (Offloading)");
                        break;
                    case 5:
                        globalDispatcher->displayByStatus("Under Maintenance");
                        break;
                    case 6:
                        globalDispatcher->displayByStatus("Refuelling / Restocking");
                        break;
                    case 7:
                        globalDispatcher->displayByLocation("Hospital HQ - Emergency Wing");
                        break;
                    case 8:
                        globalDispatcher->displayByLocation("Bandar Klang Medical Station");
                        break;
                    case 9:
                        globalDispatcher->displayByLocation("Bukit Raja Response Unit");
                        break;
                    case 10:
                        globalDispatcher->displayByLocation("Port Klang Substation");
                        break;
                    case 11:
                        globalDispatcher->displayByLocation("Kapar Health Post");
                        break;
                    case 12:
                        globalDispatcher->displayByLocation("Taman Sentosa Medical Base");
                        break;
                    case 0:
                        cout << "\n[CANCELLED] Filter cancelled.\n";
                        break;
                    default:
                        cout << "\n[ERROR] Invalid filter choice!\n";
                }
                break;
            }
            case 9:
                globalDispatcher->loadFromCSV(AMBULANCE_CSV_FILENAME);
                break;
            case 10:
                globalDispatcher->saveToCSV(AMBULANCE_CSV_FILENAME);
                break;
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please enter a number between 0-10.\n";
        }
        
        // Pause before showing menu again (except when exiting)
        if (choice != 0 && choice >= 1 && choice <= 10) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
}

