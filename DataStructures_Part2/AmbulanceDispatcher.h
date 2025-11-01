#ifndef AMBULANCE_DISPATCHER_H
#define AMBULANCE_DISPATCHER_H

#include <string>
using namespace std;

// Ambulance structure to store ambulance details
struct Ambulance {
    string ambulanceID;
    string driverName;
    string status;
    string lastDispatchTime;
    string location;
    int distanceCovered;
};

// Circular Queue class for Ambulance Dispatcher
class AmbulanceDispatcher {
private:
    static const int MAX_SIZE = 100;
    Ambulance ambulances[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    // Constructor
    AmbulanceDispatcher();

    // Check if queue is full
    bool isFull();

    // Check if queue is empty
    bool isEmpty();

    // Function 1: Register Ambulance (Add to circular queue)
    void registerAmbulance();

    // Function 2: Rotate Ambulance Shift (Circular rotation)
    void rotateAmbulanceShift();

    // Function 3: Display Ambulance Schedule (Show all in rotation order)
    void displayAmbulanceSchedule();

    // Load data from CSV file
    void loadFromCSV(string filename);

    // Save data to CSV file
    void saveToCSV(string filename);

    // Get count of ambulances
    int getCount();
};

// Menu function for Ambulance Dispatcher module
void ambulanceDispatcherMenu();

#endif // AMBULANCE_DISPATCHER_H

