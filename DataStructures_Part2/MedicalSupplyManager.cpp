#include "MedicalSupplyManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>  // For sprintf_s
using namespace std;

// Global instance for the menu system
static MedicalSupplyManager* globalSupplyManager = nullptr;

// Constructor
MedicalSupplyManager::MedicalSupplyManager() {
    top = -1;  // Stack is empty initially
}

// Check if stack is full
bool MedicalSupplyManager::isFull() {
    return top == MAX_SIZE - 1;
}

// Check if stack is empty
bool MedicalSupplyManager::isEmpty() {
    return top == -1;
}

// Function 1: Add Supply Stock (Push to stack)
void MedicalSupplyManager::addSupplyStock() {
    if (isFull()) {
        cout << "\n[ERROR] Supply storage is full! Cannot add more supplies.\n";
        return;
    }

    MedicalSupply newSupply;
    int choice;
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                          ADD NEW SUPPLY STOCK                          \n";
    cout << "=======================================================================\n";
    cout << "\n";
    
    // 1. SUPPLY ID - Auto-generate with option to customize
    cout << "1. SUPPLY ID\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // Generate next ID based on count
    char nextID[10];
    sprintf_s(nextID, "S%03d", top + 2);  // +2 because top starts at -1
    
    cout << "Suggested ID: " << nextID << "\n";
    cout << "  1. Use suggested ID (" << nextID << ")\n";
    cout << "  2. Enter custom ID\n";
    cout << "Your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        newSupply.supplyID = nextID;
    } else {
        cout << "Enter Supply ID (format: S001, S002, etc.): ";
        cin >> newSupply.supplyID;
    }
    cin.ignore();
    
    // 2. ITEM NAME - Predefined list with custom option
    cout << "\n--------------------------------------------------------------------\n";
    cout << "2. ITEM NAME\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select item from inventory:\n";
    cout << "  1. Paracetamol 500mg\n";
    cout << "  2. Ibuprofen 200mg\n";
    cout << "  3. Amoxicillin Capsules\n";
    cout << "  4. Sterile Gauze Pads\n";
    cout << "  5. Latex Gloves\n";
    cout << "  6. N95 Respirators\n";
    cout << "  7. Face Shields\n";
    cout << "  8. IV Drip Set\n";
    cout << "  9. Surgical Masks\n";
    cout << " 10. Digital Thermometer\n";
    cout << " 11. Syringes 10ml\n";
    cout << " 12. Blood Pressure Monitor\n";
    cout << " 13. Wheelchair\n";
    cout << " 14. Disinfectant Solution\n";
    cout << " 15. Hand Sanitizer\n";
    cout << " 16. Enter custom item name\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: newSupply.itemName = "Paracetamol 500mg"; break;
        case 2: newSupply.itemName = "Ibuprofen 200mg"; break;
        case 3: newSupply.itemName = "Amoxicillin Capsules"; break;
        case 4: newSupply.itemName = "Sterile Gauze Pads"; break;
        case 5: newSupply.itemName = "Latex Gloves"; break;
        case 6: newSupply.itemName = "N95 Respirators"; break;
        case 7: newSupply.itemName = "Face Shields"; break;
        case 8: newSupply.itemName = "IV Drip Set"; break;
        case 9: newSupply.itemName = "Surgical Masks"; break;
        case 10: newSupply.itemName = "Digital Thermometer"; break;
        case 11: newSupply.itemName = "Syringes 10ml"; break;
        case 12: newSupply.itemName = "Blood Pressure Monitor"; break;
        case 13: newSupply.itemName = "Wheelchair"; break;
        case 14: newSupply.itemName = "Disinfectant Solution"; break;
        case 15: newSupply.itemName = "Hand Sanitizer"; break;
        case 16:
            cout << "Enter item name: ";
            getline(cin, newSupply.itemName);
            break;
        default:
            newSupply.itemName = "Unknown Item";
    }
    
    // 3. CATEGORY - Predefined options
    cout << "\n--------------------------------------------------------------------\n";
    cout << "3. CATEGORY\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select supply category:\n";
    cout << "  1. Medicine\n";
    cout << "  2. Protective Gear\n";
    cout << "  3. Equipment\n";
    cout << "  4. Consumable\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: newSupply.category = "Medicine"; break;
        case 2: newSupply.category = "Protective Gear"; break;
        case 3: newSupply.category = "Equipment"; break;
        case 4: newSupply.category = "Consumable"; break;
        default: newSupply.category = "Consumable";
    }
    
    // 4. QUANTITY
    cout << "\n--------------------------------------------------------------------\n";
    cout << "4. QUANTITY\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Enter quantity: ";
    cin >> newSupply.quantity;
    cin.ignore();
    
    // 5. BATCH NUMBER - Auto-generate with custom option
    cout << "\n--------------------------------------------------------------------\n";
    cout << "5. BATCH NUMBER\n";
        cout << "-----------------------------------------------------------------------\n";
    
    char nextBatch[10];
    sprintf_s(nextBatch, "B%04d", 2100 + top + 1);
    
    cout << "Suggested Batch: " << nextBatch << "\n";
    cout << "  1. Use suggested batch (" << nextBatch << ")\n";
    cout << "  2. Enter custom batch number\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        newSupply.batchNumber = nextBatch;
    } else {
        cout << "Enter batch number (format: B2100, B2101, etc.): ";
        getline(cin, newSupply.batchNumber);
    }
    
    // 6. DATE ADDED
    cout << "\n--------------------------------------------------------------------\n";
    cout << "6. DATE ADDED\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Enter date added (format: YYYY-MM-DD, e.g., 2025-10-31): ";
    getline(cin, newSupply.dateAdded);
    
    // 7. STATUS - Predefined options
    cout << "\n--------------------------------------------------------------------\n";
    cout << "7. STATUS\n";
        cout << "-----------------------------------------------------------------------\n";
    cout << "Select current status:\n";
    cout << "  1. In Stock (Ready for Use)\n";
    cout << "  2. Low Stock - Reorder Soon\n";
    cout << "  3. Used in Ward - Pending Refill\n";
    cout << "  4. Expired - Awaiting Disposal\n";
    cout << "  5. Under Inspection\n";
    cout << "  6. Allocated for Surgery\n";
    cout << "  7. Quarantined Batch\n";
    cout << "  8. Restocking in Progress\n";
    cout << "Your choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1: newSupply.status = "In Stock (Ready for Use)"; break;
        case 2: newSupply.status = "Low Stock - Reorder Soon"; break;
        case 3: newSupply.status = "Used in Ward - Pending Refill"; break;
        case 4: newSupply.status = "Expired - Awaiting Disposal"; break;
        case 5: newSupply.status = "Under Inspection"; break;
        case 6: newSupply.status = "Allocated for Surgery"; break;
        case 7: newSupply.status = "Quarantined Batch"; break;
        case 8: newSupply.status = "Restocking in Progress"; break;
        default: newSupply.status = "In Stock (Ready for Use)";
    }

    // Push to stack (LIFO - Last In, First Out)
    top++;
    supplies[top] = newSupply;

    cout << "\n[SUCCESS] Supply added to stock!\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Supply ID     : " << newSupply.supplyID << "\n";
    cout << "  Item Name     : " << newSupply.itemName << "\n";
    cout << "  Category      : " << newSupply.category << "\n";
    cout << "  Quantity      : " << newSupply.quantity << "\n";
    cout << "  Batch Number  : " << newSupply.batchNumber << "\n";
    cout << "  Stack Position: " << (top + 1) << " (Most Recent)\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "\n[INFO] This supply will be used FIRST (LIFO - Last In, First Out)\n";
    
    // Auto-save to CSV
    saveToCSV("Medical_Supply_Manager_Dataset.csv");
}

// Function 2: Use 'Last Added' Supply (Pop from stack - LIFO)
void MedicalSupplyManager::useLastAddedSupply() {
    if (isEmpty()) {
        cout << "\n[ERROR] No supplies available in stock.\n";
        return;
    }

    // Get the top supply (most recently added)
    MedicalSupply usedSupply = supplies[top];
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                      USE LAST ADDED SUPPLY (LIFO)                     \n";
    cout << "=======================================================================\n";
    cout << "\n";
    
    cout << "Retrieving the MOST RECENTLY added supply:\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "  Supply ID    : " << usedSupply.supplyID << "\n";
    cout << "  Item Name    : " << usedSupply.itemName << "\n";
    cout << "  Category     : " << usedSupply.category << "\n";
    cout << "  Quantity     : " << usedSupply.quantity << "\n";
    cout << "  Batch Number : " << usedSupply.batchNumber << "\n";
    cout << "  Date Added   : " << usedSupply.dateAdded << "\n";
    cout << "  Status       : " << usedSupply.status << "\n";
    cout << "----------------------------------------------------------------------\n";
    
    // Confirm usage
    char confirm;
    cout << "\nUse this supply? (Y/N): ";
    cin >> confirm;
    
    if (confirm == 'Y' || confirm == 'y') {
        // Pop from stack
        top--;
        
        cout << "\n[SUCCESS] Supply used and removed from stock!\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "  Used Item     : " << usedSupply.itemName << "\n";
        cout << "  Quantity Used : " << usedSupply.quantity << "\n";
        cout << "  Remaining Items in Stock: " << (top + 1) << "\n";
        cout << "-----------------------------------------------------------------------\n";
        
        if (!isEmpty()) {
            cout << "\n[INFO] Next supply to be used:\n";
            cout << "       " << supplies[top].itemName 
                 << " (ID: " << supplies[top].supplyID << ")\n";
        } else {
            cout << "\n[WARNING] Stock is now empty! Please add more supplies.\n";
        }
        
        // Auto-save to CSV
        saveToCSV("Medical_Supply_Manager_Dataset.csv");
    } else {
        cout << "\n[CANCELLED] Supply usage cancelled.\n";
    }
}

// Function 3: View Current Supplies (Display all supplies in stack)
void MedicalSupplyManager::viewCurrentSupplies() {
    if (isEmpty()) {
        cout << "\n[INFO] No supplies currently in stock.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                   CURRENT SUPPLY INVENTORY (LIFO Order)                \n";
    cout << "=======================================================================\n";
    cout << "\n";
    cout << "Total Supplies in Stock: " << (top + 1) << "\n";
    cout << "Note: Items are shown from MOST RECENT (top) to OLDEST (bottom)\n";
    cout << "-----------------------------------------------------------------------\n\n";

    // Display from top to bottom (LIFO order)
    for (int i = top; i >= 0; i--) {
        if (i == top) {
            cout << ">>> NEXT TO BE USED (TOP OF STACK) <<<\n";
        } else if (i == 0) {
            cout << "\n--- OLDEST ITEM (BOTTOM OF STACK) ---\n";
        }
        
        cout << "Position " << (i + 1) << " (Stack Level " << (top - i + 1) << " from top):\n";
        cout << "  Supply ID    : " << supplies[i].supplyID << "\n";
        cout << "  Item Name    : " << supplies[i].itemName << "\n";
        cout << "  Category     : " << supplies[i].category << "\n";
        cout << "  Quantity     : " << supplies[i].quantity << "\n";
        cout << "  Batch Number : " << supplies[i].batchNumber << "\n";
        cout << "  Date Added   : " << supplies[i].dateAdded << "\n";
        cout << "  Status       : " << supplies[i].status << "\n";
        cout << "-----------------------------------------------------------------------\n";
    }
    cout << "\n";
}

// Load data from CSV file
void MedicalSupplyManager::loadFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not open " << filename << "\n";
        cout << "Please ensure the file exists in the same directory.\n";
        return;
    }

    // Clear existing data before loading
    top = -1;

    string line;
    getline(file, line); // Skip header line

    int loadedCount = 0;
    while (getline(file, line) && !isFull()) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        MedicalSupply supply;
        
        getline(ss, supply.supplyID, ',');
        getline(ss, supply.itemName, ',');
        getline(ss, supply.category, ',');
        
        string qtyStr;
        getline(ss, qtyStr, ',');
        try {
            supply.quantity = stoi(qtyStr);
        } catch (...) {
            supply.quantity = 0;
        }
        
        getline(ss, supply.batchNumber, ',');
        getline(ss, supply.dateAdded, ',');
        getline(ss, supply.status);

        // Push to stack
        top++;
        supplies[top] = supply;
        loadedCount++;
    }

    file.close();
    cout << "\n[SUCCESS] Loaded " << loadedCount << " supplies from " << filename << "\n";
    cout << "[INFO] Supplies loaded in LIFO order - most recent at top of stack.\n";
}

// Save data to CSV file
void MedicalSupplyManager::saveToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not create/open " << filename << " for writing.\n";
        return;
    }

    // Write CSV header
    file << "Supply ID,Item Name,Category,Quantity,Batch Number,Date Added,Status\n";

    // Write all supplies in reverse order (top to bottom, LIFO order)
    for (int i = top; i >= 0; i--) {
        file << supplies[i].supplyID << ","
             << supplies[i].itemName << ","
             << supplies[i].category << ","
             << supplies[i].quantity << ","
             << supplies[i].batchNumber << ","
             << supplies[i].dateAdded << ","
             << supplies[i].status << "\n";
    }

    file.close();
    cout << "\n[SUCCESS] Saved " << (top + 1) << " supplies to " << filename << "\n";
}

// Get count of supplies
int MedicalSupplyManager::getCount() {
    return top + 1;
}

// Menu function for Medical Supply Manager module
void medicalSupplyManagerMenu() {
    // Create supply manager instance if not exists
    if (globalSupplyManager == nullptr) {
        globalSupplyManager = new MedicalSupplyManager();
        // Auto-load data from CSV on first entry
        globalSupplyManager->loadFromCSV("Medical_Supply_Manager_Dataset.csv");
    }
    
    int choice;
    
    do {
        cout << "\n";
        cout << "=======================================================================\n";
        cout << "                         MEDICAL SUPPLY MANAGER                       \n";
        cout << "                           (Stack System - LIFO)                      \n";
        cout << "=======================================================================\n";
        cout << "\nOPTIONS:\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "  1. Add Supply Stock\n";
        cout << "  2. Use 'Last Added' Supply (LIFO)\n";
        cout << "  3. View Current Supplies\n";
        cout << "  4. Load Data from CSV (Reload)\n";
        cout << "  5. Save Data to CSV\n";
        cout << "  0. Return to Main Menu\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                globalSupplyManager->addSupplyStock();
                break;
            case 2:
                globalSupplyManager->useLastAddedSupply();
                break;
            case 3:
                globalSupplyManager->viewCurrentSupplies();
                break;
            case 4:
                globalSupplyManager->loadFromCSV("Medical_Supply_Manager_Dataset.csv");
                break;
            case 5:
                globalSupplyManager->saveToCSV("Medical_Supply_Manager_Dataset.csv");
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

