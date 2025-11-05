#ifndef MEDICAL_SUPPLY_MANAGER_H
#define MEDICAL_SUPPLY_MANAGER_H

#include <string>
#include <iostream>

using namespace std;

// Medical supply data structure
struct MedicalSupply {
    string supplyID;
    string itemName;
    string category;
    int quantity;
    string batchNumber;
    string dateAdded;
    string status;
};

// Stack node structure
struct Node {
    MedicalSupply data;
    Node* next;
};

// Medical supply manager using LIFO stack
class MedicalSupplyManager {
private:
    Node* top;
    void addSupplyStock_Engine(MedicalSupply newSupply);

public:
    MedicalSupplyManager();
    ~MedicalSupplyManager();

    bool isEmpty();
    int getCount();

    void addSupplyStock();
    void useLastAddedSupply();
    void viewCurrentSupplies();
    void loadFromCSV(string filename);
    void saveToCSV(string filename);
};

void medicalSupplyManagerMenu();

#endif 