#ifndef PAC_HPP
#define PAC_HPP

#include <string>

class PAC {
public:
    // ----- Domain model -----
    struct Patient {
        int id;                     
        std::string name;           
        std::string conditionType;  
        std::string admittedAt;     
    };

private:
    struct Node {
        Patient data;
        Node* next;
        explicit Node(const Patient& p) : data(p), next(nullptr) {}
    };

    Node* front_;   
    Node* rear_;    
    int   count_;   

public:
    // ----- Lifecycle -----
    PAC();
    ~PAC();

    // ----- Core PAC functionalities -----
    void admitPatient(int id, const std::string& name, const std::string& conditionType,
                      const std::string& admittedAt = "");
    // Returns false if queue is empty; out receives discharged patient
    bool dischargePatient(PAC::Patient& out);
    void viewQueue() const; // prints a simple table to std::cout

    // ----- Utilities -----
    bool isEmpty() const;
    int  size() const;

    // Peek earliest (returns false if empty)
    bool peek(PAC::Patient& out) const;

    // Optional CSV I/O for demo/persistence (schema below)
    // Header: patient_id,name,condition_type,admitted_at
    bool loadFromCSV(const std::string& filename); // clears then loads
    bool saveToCSV(const std::string& filename) const;

    // Non-copyable (raw pointers)
    PAC(const PAC&) = delete;
    PAC& operator=(const PAC&) = delete;
};

#endif // PAC_HPP
