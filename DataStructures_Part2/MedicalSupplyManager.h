#ifndef MEDICAL_SUPPLY_MANAGER_H
#define MEDICAL_SUPPLY_MANAGER_H

#include <string>
using namespace std;

// Medical Supply structure to store supply details
struct MedicalSupply {
    string supplyID;
    string itemName;
    string category;
    int quantity;
    string batchNumber;
    string dateAdded;
    string status;
};

// Stack class for Medical Supply Manager
class MedicalSupplyManager {
private:
    static const int MAX_SIZE = 100;
    MedicalSupply supplies[MAX_SIZE];
    int top;  // Points to the top of the stack

public:
    // Constructor
    MedicalSupplyManager();

    // Check if stack is full
    bool isFull();

    // Check if stack is empty
    bool isEmpty();

    // Function 1: Add Supply Stock (Push to stack)
    void addSupplyStock();

    // Function 2: Use 'Last Added' Supply (Pop from stack - LIFO)
    void useLastAddedSupply();

    // Function 3: View Current Supplies (Display all supplies in stack)
    void viewCurrentSupplies();

    // Load data from CSV file
    void loadFromCSV(string filename);

    // Save data to CSV file
    void saveToCSV(string filename);

    // Get count of supplies
    int getCount();
};

// Menu function for Medical Supply Manager module
void medicalSupplyManagerMenu();

#endif // MEDICAL_SUPPLY_MANAGER_H

