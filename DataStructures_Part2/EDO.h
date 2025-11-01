#ifndef EDO_H
#define EDO_H

#include <iostream>
#include <string>
#include <fstream>

/*
===========================================================
 Emergency Department Officer (EDO) Module
 ----------------------------------------------------------
 Role:
  - Handles emergency admission records and ensures that the
    most critical cases are always processed first.
  - Implements three core functions:
       (1) Log Emergency Case
       (2) Process Most Critical Case
       (3) View Pending Emergency Cases
 ----------------------------------------------------------
 Data Structure Used:
  - Fixed-size static array of EmergencyCase structs (pq[]),
    sorted by priority level.
  - Manual insertion sorting ensures the array remains ordered
    (no STL containers such as vector/list are used).
 ----------------------------------------------------------
 Design Objective:
  - Demonstrate knowledge of custom data management,
    sorting logic, and array-based priority queue concepts
    using only core C++ language constructs.
===========================================================
*/

const int MAX_CASES = 200; // Maximum number of emergency cases stored (static array only)

//----------------------------------------------------------
// Structure: EmergencyCase
// Purpose :  Represents a single emergency record.
// Fields  :
//   caseID        - Unique numeric identifier
//   patientName   - Full name of the patient
//   emergencyType - Description of emergency (e.g., Trauma, Cardiac, Respiratory)
//   priorityLevel - Integer priority scale (1 = Critical ... 5 = Minor)
//   arrivalTime   - Timestamp or textual entry of arrival
//   status        - Case state ("Waiting", "Processed", etc.)
//----------------------------------------------------------
struct EmergencyCase {
    int caseID;
    std::string patientName;
    std::string emergencyType;
    int priorityLevel;
    std::string arrivalTime;
    std::string status;
};

//----------------------------------------------------------
// Class: EDO
// Purpose:
//   Implements a simple array-based Priority Queue
//   for managing emergency cases by priority order.
//   The array remains sorted so that the most critical
//   case is always accessible from index 0.
//
// Core Features:
//   • Log Emergency Case (Insertion in sorted order)
//   • Process Most Critical Case (Removal from front)
//   • View All Cases (Display ordered list)
//   • Optional CSV file I/O for demo or persistence
//----------------------------------------------------------
class EDO {
private:
    EmergencyCase pq[MAX_CASES]; // Fixed array representing a priority queue
    int size;                    // Current number of active records

    //------------------------------------------------------
    // Helper Function: insertSorted
    // Purpose:
    //   Inserts a new EmergencyCase into pq[] in sorted order
    //   based on priority level. Lower integer = higher priority.
    //   Insertion shifts elements to maintain sorted structure.
    //------------------------------------------------------
    void insertSorted(const EmergencyCase &ec);

    //------------------------------------------------------
    // Helper Function: printHeader
    // Purpose:
    //   Prints column titles neatly formatted for case listings.
    //------------------------------------------------------
    void printHeader() const;

    //------------------------------------------------------
    // Helper Function: printCase
    // Purpose:
    //   Displays a single EmergencyCase in a formatted line.
    //------------------------------------------------------
    void printCase(const EmergencyCase &ec) const;

public:
    //------------------------------------------------------
    // Constructor: EDO()
    // Purpose:
    //   Initializes an empty emergency record list.
    //------------------------------------------------------
    EDO();

    //------------------------------------------------------
    // Function: logCase
    // Purpose:
    //   Logs a new emergency record into the queue.
    //   Automatically places it according to priority order.
    // Parameters:
    //   caseID        - unique case identifier
    //   patientName   - name of patient
    //   emergencyType - type/category of emergency
    //   priorityLevel - 1 = highest priority, larger = lower
    //   arrivalTime   - time of arrival
    //   status        - current state (e.g., "Waiting")
    // Returns:
    //   true if inserted successfully, false if queue is full.
    //------------------------------------------------------
    bool logCase(int caseID,
                 const std::string &patientName,
                 const std::string &emergencyType,
                 int priorityLevel,
                 const std::string &arrivalTime,
                 const std::string &status);

    //------------------------------------------------------
    // Function: processMostCritical
    // Purpose:
    //   Removes and returns the most critical emergency case
    //   (first element in sorted array). Shifts others forward.
    // Parameters:
    //   outProcessed - reference to store removed record
    // Returns:
    //   true if a case was processed, false if queue was empty.
    //------------------------------------------------------
    bool processMostCritical(EmergencyCase &outProcessed);

    //------------------------------------------------------
    // Function: viewAll
    // Purpose:
    //   Displays all pending cases sorted by priority.
    //   Read-only operation; does not alter internal data.
    //------------------------------------------------------
    void viewAll() const;

    //------------------------------------------------------
    // Function: loadCSV
    // Purpose:
    //   Loads emergency cases from a CSV file.
    //   Useful for demonstration or testing.
    // Returns:
    //   true if loaded successfully, false on error.
    //------------------------------------------------------
    bool loadCSV(const std::string &path);

    //------------------------------------------------------
    // Function: saveCSV
    // Purpose:
    //   Exports all current emergency cases into a CSV file.
    // Returns:
    //   true if saved successfully, false on error.
    //------------------------------------------------------
    bool saveCSV(const std::string &path) const;

    //------------------------------------------------------
    // Utility Functions:
    //   isFull()  - returns true if pq[] has reached MAX_CASES
    //   isEmpty() - returns true if no active records
    //   count()   - returns current number of stored cases
    //------------------------------------------------------
    bool isFull() const { return size >= MAX_CASES; }
    bool isEmpty() const { return size <= 0; }
    int count() const { return size; }
};

//----------------------------------------------------------
// Function: emergencyDepartmentOfficerMenu
// Purpose:
//   Menu-driven interface for the EDO module.
//   Integrates with the main hospital management system.
//----------------------------------------------------------
void emergencyDepartmentOfficerMenu();

#endif // EDO_H
