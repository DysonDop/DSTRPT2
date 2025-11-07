#include "MedicalSupplyManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// Global instance for menu operations
static MedicalSupplyManager* globalSupplyManager = nullptr;

// Initialize empty stack
MedicalSupplyManager::MedicalSupplyManager() {
    top = nullptr;
}

// Clean up all nodes to prevent memory leaks
MedicalSupplyManager::~MedicalSupplyManager() {
    while (!isEmpty()) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

// Check if stack is empty
bool MedicalSupplyManager::isEmpty() {
    return top == nullptr;
}

// Count total items in stack
int MedicalSupplyManager::getCount() {
    int count = 0;
    Node* current = top;
    
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Push new supply to top of stack
void MedicalSupplyManager::addSupplyStock_Engine(MedicalSupply newSupply) {
    Node* newNode = new Node();
    newNode->data = newSupply;
    newNode->next = top;
    top = newNode;
}

// Interactive menu to add new supply
void MedicalSupplyManager::addSupplyStock() {
    MedicalSupply newSupply;
    int choice;
    
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                      ADD NEW SUPPLY STOCK                             \n";
    cout << "=======================================================================\n";
    cout << "\n";
    
    // Supply ID input
    cout << "1. SUPPLY ID\n";
    cout << "-----------------------------------------------------------------------\n";
    
    stringstream ss;
    ss << "S" << setfill('0') << setw(3) << (getCount() + 1);
    string nextID = ss.str();
    
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Item name selection
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
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

    // Category selection
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
        case 1: newSupply.category = "Medicine"; break;
        case 2: newSupply.category = "Protective Gear"; break;
        case 3: newSupply.category = "Equipment"; break;
        case 4: newSupply.category = "Consumable"; break;
        default: newSupply.category = "Consumable";
    }
    
    // Quantity input with validation
    cout << "\n--------------------------------------------------------------------\n";
    cout << "4. QUANTITY\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Enter quantity: ";
    while (!(cin >> newSupply.quantity)) {
        cout << "[ERROR] Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Batch number input
    cout << "\n5. BATCH NUMBER\n";
    cout << "-----------------------------------------------------------------------\n";
    
    stringstream ssBatch;
    ssBatch << "B" << setfill('0') << setw(4) << (2100 + getCount());
    string nextBatch = ssBatch.str();
    
    cout << "Suggested Batch: " << nextBatch << "\n";
    cout << "  1. Use suggested batch (" << nextBatch << ")\n";
    cout << "  2. Enter custom batch number\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (choice == 1) {
        newSupply.batchNumber = nextBatch;
    } else {
        cout << "Enter batch number (format: B2100, B2101, etc.): ";
        getline(cin, newSupply.batchNumber);
    }

    // Date input
    cout << "\n--------------------------------------------------------------------\n";
    cout << "6. DATE ADDED\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Enter date added (format: YYYY-MM-DD, e.g., 2025-10-31): ";
    getline(cin, newSupply.dateAdded);
    
    // Status selection
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    // Add supply to stack
    addSupplyStock_Engine(newSupply);

    cout << "\n[SUCCESS] Supply added to stock!\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "  Stack Position: " << getCount() << " (Most Recent)\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "\n[INFO] This supply will be used FIRST (LIFO - Last In, First Out)\n";
    
    saveToCSV("Medical_Supply_Manager_Dataset.csv");
}

// Remove most recently added supply (LIFO pop)
void MedicalSupplyManager::useLastAddedSupply() {
    if (isEmpty()) {
        cout << "\n[ERROR] No supplies available in stock.\n";
        return;
    }

    Node* temp = top;
    MedicalSupply usedSupply = top->data;
    
    // Display supply to be used
    cout << "\n";
    cout << "=======================================================================\n";
    cout << "                  USE LAST ADDED SUPPLY (LIFO)                         \n";
    cout << "=======================================================================\n";
    cout << "\nRetrieving the MOST RECENTLY added supply:\n";
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (confirm == 'Y' || confirm == 'y') {
        // Pop from stack
        top = top->next;
        delete temp;
        
        cout << "\n[SUCCESS] Supply used and removed from stock!\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "  Used Item     : " << usedSupply.itemName << "\n";
        cout << "  Quantity Used : " << usedSupply.quantity << "\n";
        cout << "  Remaining Items in Stock: " << getCount() << "\n";
        cout << "-----------------------------------------------------------------------\n";
        
        // Show next supply in queue
        if (!isEmpty()) {
            cout << "\n[INFO] Next supply to be used:\n";
            cout << "        " << top->data.itemName 
                 << " (ID: " << top->data.supplyID << ")\n";
        } else {
            cout << "\n[WARNING] Stock is now empty! Please add more supplies.\n";
        }
        
        saveToCSV("Medical_Supply_Manager_Dataset.csv");
    } else {
        cout << "\n[CANCELLED] Supply usage cancelled.\n";
    }
}

// Display all supplies in stack order
void MedicalSupplyManager::viewCurrentSupplies() {
    if (isEmpty()) {
        cout << "\n[INFO] No supplies currently in stock.\n";
        return;
    }

    cout << "\n";
    cout << "=======================================================================\n";
    cout << "             CURRENT SUPPLY INVENTORY (LIFO Order)                     \n";
    cout << "=======================================================================\n";
    cout << "\nTotal Supplies in Stock: " << getCount() << "\n";
    cout << "Note: Items are shown from MOST RECENT (top) to OLDEST (bottom)\n";
    cout << "-----------------------------------------------------------------------\n\n";

    Node* current = top;
    int position = 1;
    
    while (current != nullptr) {
        if (current == top) {
            cout << ">>> NEXT TO BE USED (TOP OF STACK) <<<\n";
        }
        
        // Display current node data
        cout << "Position " << position << " (Stack Level " << position << " from top):\n";
        cout << "  Supply ID    : " << current->data.supplyID << "\n";
        cout << "  Item Name    : " << current->data.itemName << "\n";
        cout << "  Category     : " << current->data.category << "\n";
        cout << "  Quantity     : " << current->data.quantity << "\n";
        cout << "  Batch Number : " << current->data.batchNumber << "\n";
        cout << "  Date Added   : " << current->data.dateAdded << "\n";
        cout << "  Status       : " << current->data.status << "\n";
        cout << "-----------------------------------------------------------------------\n";

        if (current->next == nullptr && position > 1) {
             cout << "\n--- OLDEST ITEM (BOTTOM OF STACK) ---\n";
        }
        
        // Move to next node
        current = current->next;
        position++;
    }
    cout << "\n";
}

// Load supplies from CSV file
void MedicalSupplyManager::loadFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not open " << filename << "\n";
        return;
    }

    // Clear existing stack
    while (!isEmpty()) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    string line;
    getline(file, line); // Skip header

    int loadedCount = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        MedicalSupply supply;
        
        // Parse CSV fields
        getline(ss, supply.supplyID, ',');
        getline(ss, supply.itemName, ',');
        getline(ss, supply.category, ',');
        
        string qtyStr;
        getline(ss, qtyStr, ',');
        try { supply.quantity = stoi(qtyStr); } catch (...) { supply.quantity = 0; }
        
        getline(ss, supply.batchNumber, ',');
        getline(ss, supply.dateAdded, ',');
        getline(ss, supply.status);

        // Add to stack
        addSupplyStock_Engine(supply);
        loadedCount++;
    }

    file.close();
    cout << "\n[SUCCESS] Loaded " << loadedCount << " supplies from " << filename << "\n";
}

// Save current stack to CSV file
void MedicalSupplyManager::saveToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "\n[WARNING] Could not create/open " << filename << " for writing.\n";
        return;
    }

    // Write CSV header
    file << "Supply ID,Item Name,Category,Quantity,Batch Number,Date Added,Status\n";

    // Write all supplies
    Node* current = top;
    while (current != nullptr) {
        file << current->data.supplyID << ","
             << "\"" << current->data.itemName << "\","
             << "\"" << current->data.category << "\","
             << current->data.quantity << ","
             << "\"" << current->data.batchNumber << "\","
             << "\"" << current->data.dateAdded << "\","
             << "\"" << current->data.status << "\"\n";
        current = current->next;
    }

    file.close();
    cout << "\n[SUCCESS] Saved " << getCount() << " supplies to " << filename << "\n";
}


// Main menu interface for medical supply manager
void medicalSupplyManagerMenu() {
    // Create manager instance if needed
    if (globalSupplyManager == nullptr) {
        globalSupplyManager = new MedicalSupplyManager();
        globalSupplyManager->loadFromCSV("Medical_Supply_Manager_Dataset.csv");
    }
    
    int choice;
    do {
        cout << "\n";
        cout << "=======================================================================\n";
        cout << "                      MEDICAL SUPPLY MANAGER                         \n";
        cout << "                      (Stack System - LIFO)                          \n";
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
        
        // Get and validate input
        while (!(cin >> choice)) {
            cout << "[ERROR] Invalid choice. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Process menu choice
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
                // Clean up memory
                delete globalSupplyManager;
                globalSupplyManager = nullptr;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please enter a number between 0-5.\n";
        }
        
    } while (choice != 0);
}