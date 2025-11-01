#ifndef PAC_H
#define PAC_H

#include <string>

/*
===========================================================
 Patient Admission Clerk (PAC) Module
 ----------------------------------------------------------
 Role:
  - Manages patient admissions in a First-In-First-Out (FIFO)
    order, ensuring fair and orderly processing.
  - Implements three core functions:
       (1) Admit Patient
       (2) Discharge Earliest Patient
       (3) View Patient Queue
 ----------------------------------------------------------
 Data Structure Used:
  - Singly linked list implementing a Queue (FIFO)
  - Dynamic memory management with manual node allocation
  - No STL containers (vector/list/queue) are used
 ----------------------------------------------------------
 Design Objective:
  - Demonstrate knowledge of custom queue implementation,
    dynamic memory management, and linked list concepts
    using only core C++ language constructs.
===========================================================
*/

//----------------------------------------------------------
// Class: PAC (Patient Admission Clerk)
// Purpose:
//   Implements a queue-based system for managing patient
//   admissions. Patients are processed in the order they
//   arrive (FIFO - First In, First Out).
//
// Core Features:
//   • Admit Patient (Enqueue at rear)
//   • Discharge Patient (Dequeue from front)
//   • View Queue (Display all patients in order)
//   • Optional CSV file I/O for demo or persistence
//----------------------------------------------------------
class PAC {
public:
    //------------------------------------------------------
    // Structure: Patient
    // Purpose:  Represents a single patient record.
    // Fields:
    //   id            - Unique numeric identifier
    //   name          - Full name of the patient
    //   conditionType - Type of condition (e.g., Surgery, Emergency, General)
    //   admittedAt    - Timestamp of admission (ISO-8601 format)
    //------------------------------------------------------
    struct Patient {
        int id;                     
        std::string name;           
        std::string conditionType;  
        std::string admittedAt;     
    };

private:
    //------------------------------------------------------
    // Structure: Node
    // Purpose:  Internal linked list node for queue implementation.
    //------------------------------------------------------
    struct Node {
        Patient data;
        Node* next;
        explicit Node(const Patient& p) : data(p), next(nullptr) {}
    };

    Node* front_;   // Points to the first patient in queue
    Node* rear_;    // Points to the last patient in queue
    int   count_;   // Current number of patients in queue

    //------------------------------------------------------
    // Helper Function: trim
    // Purpose:  Removes leading/trailing whitespace from strings.
    //------------------------------------------------------
    static std::string trim(const std::string& s);

public:
    //------------------------------------------------------
    // Constructor: PAC()
    // Purpose:  Initializes an empty patient queue.
    //------------------------------------------------------
    PAC();

    //------------------------------------------------------
    // Destructor: ~PAC()
    // Purpose:  Releases all dynamically allocated nodes.
    //------------------------------------------------------
    ~PAC();

    //------------------------------------------------------
    // Function: admitPatient
    // Purpose:
    //   Admits a new patient to the queue (enqueue operation).
    //   Patient is added to the rear of the queue.
    // Parameters:
    //   id            - unique patient identifier
    //   name          - patient's full name
    //   conditionType - type of medical condition
    //   admittedAt    - timestamp of admission (optional)
    //------------------------------------------------------
    void admitPatient(int id, const std::string& name, const std::string& conditionType,
                      const std::string& admittedAt = "");

    //------------------------------------------------------
    // Function: dischargePatient
    // Purpose:
    //   Discharges the earliest admitted patient (dequeue operation).
    //   Removes patient from the front of the queue.
    // Parameters:
    //   out - reference to store discharged patient data
    // Returns:
    //   true if a patient was discharged, false if queue was empty.
    //------------------------------------------------------
    bool dischargePatient(PAC::Patient& out);

    //------------------------------------------------------
    // Function: viewQueue
    // Purpose:
    //   Displays all patients in the queue in FIFO order.
    //   Read-only operation; does not alter internal data.
    //------------------------------------------------------
    void viewQueue() const;

    //------------------------------------------------------
    // Utility Functions:
    //   isEmpty() - returns true if no patients in queue
    //   size()    - returns current number of patients
    //   peek()    - views front patient without removing
    //------------------------------------------------------
    bool isEmpty() const;
    int  size() const;
    bool peek(PAC::Patient& out) const;

    //------------------------------------------------------
    // Function: loadFromCSV
    // Purpose:
    //   Loads patient records from a CSV file.
    //   Clears current queue before loading.
    // CSV Schema: patient_id,name,condition_type,admitted_at
    // Returns:
    //   true if loaded successfully, false on error.
    //------------------------------------------------------
    bool loadFromCSV(const std::string& filename);

    //------------------------------------------------------
    // Function: saveToCSV
    // Purpose:
    //   Exports all current patient records to a CSV file.
    // Returns:
    //   true if saved successfully, false on error.
    //------------------------------------------------------
    bool saveToCSV(const std::string& filename) const;

    //------------------------------------------------------
    // Non-copyable (using raw pointers for manual memory management)
    //------------------------------------------------------
    PAC(const PAC&) = delete;
    PAC& operator=(const PAC&) = delete;
};

//----------------------------------------------------------
// Function: patientAdmissionClerkMenu
// Purpose:
//   Menu-driven interface for the PAC module.
//   Integrates with the main hospital management system.
//----------------------------------------------------------
void patientAdmissionClerkMenu();

#endif // PAC_H
