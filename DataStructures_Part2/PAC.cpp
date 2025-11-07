#include "PAC.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

// Implementation of trim helper function
std::string PAC::trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    return s.substr(a, b - a + 1);
}

// Constructor
PAC::PAC() : front_(nullptr), rear_(nullptr), count_(0) {}

// Destructor
PAC::~PAC() {
    Node* cur = front_;
    while (cur) { 
        Node* nxt = cur->next; 
        delete cur; 
        cur = nxt; 
    }
    front_ = rear_ = nullptr; 
    count_ = 0;
}

// Core PAC functionalities
void PAC::admitPatient(int id, const std::string& name, const std::string& conditionType,
                  const std::string& admittedAt) {
    Patient p{ id, name, conditionType, admittedAt };
    Node* n = new Node(p);
    if (!rear_) { 
        front_ = rear_ = n; 
    }
    else { 
        rear_->next = n; 
        rear_ = n; 
    }
    ++count_;
}

bool PAC::dischargePatient(Patient& out) {
    if (!front_) return false;
    Node* n = front_;
    out = n->data;
    front_ = front_->next;
    if (!front_) rear_ = nullptr;
    delete n; 
    --count_;
    return true;
}

void PAC::viewQueue() const {
    if (!front_) {
        std::cout << "[Info] No patients in queue.\n";
        return;
    }
    std::cout << "----- Patient Admission Queue (FIFO) -----\n";
    std::cout << "Pos" << "  ";
    std::cout << "ID" << "    ";
    std::cout << "Name" << "              ";
    std::cout << "Condition" << "         ";
    std::cout << "AdmittedAt\n";
    std::cout << "------------------------------------------------------------\n";

    int pos = 1;
    for (Node* cur = front_; cur; cur = cur->next, ++pos) {
        const Patient& p = cur->data;

        std::cout << pos;
        for (int i = 0; i < (5 - std::to_string(pos).length()); ++i) {
            std::cout << " ";
        }

        std::cout << p.id;
        for (int i = 0; i < (6 - std::to_string(p.id).length()); ++i) {
            std::cout << " ";
        }

        std::cout << p.name;
        for (int i = 0; i < (18 - p.name.length()); ++i) {
            std::cout << " ";
        }

        std::cout << p.conditionType;
        for (int i = 0; i < (18 - p.conditionType.length()); ++i) {
            std::cout << " ";
        }

        std::cout << (p.admittedAt.empty() ? "-" : p.admittedAt) << "\n";
    }
}

// Utilities
bool PAC::isEmpty() const { 
    return front_ == nullptr; 
}

int PAC::size() const { 
    return count_; 
}

bool PAC::peek(Patient& out) const { 
    if (!front_) return false; 
    out = front_->data; 
    return true; 
}

// CSV I/O (header: patient_id,name,condition_type,admitted_at)
bool PAC::loadFromCSV(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    // clear current queue
    Patient dummy; 
    while (dischargePatient(dummy)) {}

    std::string line;

    // Try read first line; if not a header, parse it as data
    if (std::getline(in, line)) {
        std::stringstream test(line);
        std::string firstToken; 
        std::getline(test, firstToken, ',');
        bool header = false;
        for (char c : firstToken) { 
            if (std::isalpha(static_cast<unsigned char>(c))) { 
                header = true; 
                break; 
            } 
        }
        if (!header) {
            std::stringstream ss(line);
            std::string idStr,name,cond,admitted;
            std::getline(ss,idStr,','); 
            std::getline(ss,name,',');
            std::getline(ss,cond,','); 
            std::getline(ss,admitted,',');
            int id=0; 
            try { 
                id = std::stoi(trim(idStr)); 
            } catch (...) { 
                id = 0; 
            }
            admitPatient(id, trim(name), trim(cond), trim(admitted));
        }
    }

    while (std::getline(in, line)) {
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::stringstream ss(line);
        std::string idStr,name,cond,admitted;
        std::getline(ss,idStr,','); 
        std::getline(ss,name,',');
        std::getline(ss,cond,','); 
        std::getline(ss,admitted,',');
        int id=0; 
        try { 
            id = std::stoi(trim(idStr)); 
        } catch (...) { 
            id = 0; 
        }
        admitPatient(id, trim(name), trim(cond), trim(admitted));
    }
    return true;
}

bool PAC::saveToCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    out << "patient_id,name,condition_type,admitted_at\n";
    for (Node* cur = front_; cur; cur = cur->next) {
        const Patient& p = cur->data;
        out << p.id << "," << p.name << "," << p.conditionType << "," << p.admittedAt << "\n";
    }
    return true;
}

// ----- Dashboard (replaces main) -----
static void pause_console() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void patientAdmissionClerkMenu() {
    PAC pac;
    int choice = -1;

    std::cout << "\n[Info] Attempting to auto-load 'pac_sample.csv'...\n";
    if (pac.loadFromCSV("pac_sample.csv")) {
        std::cout << "[OK] Patient data loaded. " << pac.size() << " patients in queue.\n";
    }
    else {
        std::cout << "[Warn] 'pac_sample.csv' not found. Starting with an empty queue.\n";
    }

    while (true) {
        std::cout << "\n===== Patient Admission Clerk (PAC) =====\n"
                  << "1. Admit Patient\n"
                  << "2. Discharge Earliest Patient\n"
                  << "3. View Patient Queue\n"
                  << "4. Reload from CSV (pac_sample.csv)\n"
                  << "5. Save to CSV (pac_sample.csv)\n"
                  << "0. Return to Main Menu\n"
                  << "Choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;

        if (choice == 1) {
            int id;
            std::string name, cond, ts;
            std::string inputLine;

            // --- 1. BULLETPROOF VALIDATED ID INPUT ---
            while (true) {
                std::cout << "Enter ID: "; // Ask for ID INSIDE the loop
                std::getline(std::cin, inputLine); // Read the ENTIRE line

                std::stringstream ss(inputLine);
                char extraChar;

                if (ss >> id && !(ss >> extraChar)) {
                    // Success! It's a valid integer AND nothing else is on the line.
                    break;
                }
                else {
                    // Failed.
                    std::cout << "[Error] Invalid input. Please enter ONLY a number for the ID.\n";
                }
            }

            // --- 2. VALIDATED NAME INPUT ---
            while (true) {
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);

                if (name.empty()) { // Check if the user just pressed Enter
                    std::cout << "[Error] Name cannot be blank. Please re-enter.\n";
                }
                else {
                    break; // Good, the name is not empty, exit the loop
                }
            }

            // --- 3. VALIDATED CONDITION INPUT ---
            while (true) {
                std::cout << "Enter Condition Type: ";
                std::getline(std::cin, cond);

                if (cond.empty()) {
                    std::cout << "[Error] Condition cannot be blank. Please re-enter.\n";
                }
                else {
                    break;
                }
            }

            // --- 4. OPTIONAL TIMESTAMP ---
            std::cout << "Enter Admitted At (YYYY-MM-DDThh:mm, optional): ";
            std::getline(std::cin, ts);

            // --- 5. ADMIT THE PATIENT ---
            pac.admitPatient(id, name, cond, ts);
            std::cout << "[OK] Patient admitted. Size = " << pac.size() << "\n";
            pause_console();
        } else if (choice == 2) {

            PAC::Patient out;

            if (pac.dischargePatient(out)) {

                std::cout << "[OK] Discharged: " << out.id << " - " << out.name << "\n";

            }
            else {

                std::cout << "[Warn] Queue is empty.\n";

            }

            pause_console();

        }
        else if (choice == 3) {

            pac.viewQueue();

            pause_console();

        }
        else if (choice == 4) {

            std::string file = "pac_sample.csv";

            std::cout << "[Info] Reloading all data from '" << file << "'...\n";



            if (pac.loadFromCSV(file))

                std::cout << "[OK] Reloaded. " << pac.size() << " patients in queue.\n";

            else

                std::cout << "[Error] Could not load '" << file << "'.\n";

            pause_console();

        }
        else if (choice == 5) {

            std::string file = "pac_sample.csv"; // Hard-code the filename

            std::cout << "[Info] Saving current queue to '" << file << "'...\n";



            if (pac.saveToCSV(file))

                std::cout << "[OK] Saved. " << pac.size() << " patients in queue.\n";

            else

                std::cout << "[Error] Could not save to '" << file << "'.\n";

            pause_console();

        }

    }
}
