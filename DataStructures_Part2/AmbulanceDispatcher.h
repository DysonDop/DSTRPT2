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

    // Function 4: Search Ambulance (by ID or Driver Name)
    void searchAmbulance();
    int findAmbulanceIndexByID(string id);
    int findAmbulanceIndexByDriver(string driverName);

    // Function 5: Update Ambulance Details
    void updateAmbulanceDetails();
    bool updateAmbulanceStatus(string id, string newStatus);

    // Function 6: Remove Ambulance from Queue
    void removeAmbulanceFromQueue();
    bool removeAmbulanceByID(string id);

    // Function 7: Display Queue Statistics
    void displayQueueStatistics();
    int getTotalDistanceCovered();
    double getAverageDistance();
    int getAvailableCount();
    int getBusyCount();

    // Function 8: Filter Display Options
    void displayByStatus(string status);
    void displayByLocation(string location);
    void displayAvailableAmbulances();

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

