#include "EDO.h"
#include <sstream>

static const std::string DATA_FILE = "emergency_cases.csv";

/* Initializes an empty, sorted-by-priority structure.
   Invariant: pq[0] is always the most critical (lowest priorityLevel). */
EDO::EDO() : size(0) {}

/* insertSorted
   Purpose: Keep pq[] sorted ascending by priorityLevel (1 is most critical).
   Stability: Equal priorities keep arrival order (new items placed after equals).
   Complexity: O(n) due to shifting in a fixed array. */
void EDO::insertSorted(const EmergencyCase &ec) {
    if (isFull()) return;

    int pos = size;
    // Find first element with STRICTLY lower number (i.e., higher priority).
    // Equal priority => no break => stable insertion at the end of the equal block.
    for (int i = 0; i < size; ++i) {
        if (ec.priorityLevel < pq[i].priorityLevel) {
            pos = i;
            break;
        }
    }

    // Shift right to make space at pos.
    for (int j = size; j > pos; --j) {
        pq[j] = pq[j - 1];
    }

    pq[pos] = ec;
    ++size;
}

/* logCase
   Validates and inserts a new case in priority order.
   Notes:
     - Priority clamped to [1..9] (UI suggests 1..5; clamping is broader for safety).
     - Returns false only if structure is full. */
bool EDO::logCase(int caseID,
                  const std::string &patientName,
                  const std::string &emergencyType,
                  int priorityLevel,
                  const std::string &arrivalTime,
                  const std::string &status) {
    if (isFull()) {
        std::cout << "[!] Queue is full. Cannot add more cases.\n";
        return false;
    }

    if (priorityLevel < 1) priorityLevel = 1;
    if (priorityLevel > 9) priorityLevel = 9;

    EmergencyCase ec;
    ec.caseID = caseID;
    ec.patientName = patientName;
    ec.emergencyType = emergencyType;
    ec.priorityLevel = priorityLevel;
    ec.arrivalTime = arrivalTime;
    ec.status = status;

    insertSorted(ec);
    return true;
}

/* processMostCritical
   Removes pq[0] (most critical) and compacts the array.
   Complexity: O(n) due to left-shift. */
bool EDO::processMostCritical(EmergencyCase &outProcessed) {
    if (isEmpty()) {
        std::cout << "[!] No cases to process.\n";
        return false;
    }

    outProcessed = pq[0];

    for (int i = 1; i < size; ++i) {
        pq[i - 1] = pq[i];
    }

    --size;
    return true;
}

/* Console helpers for aligned output (header + single row). */
void EDO::printHeader() const {
    std::cout << "CaseID | Priority | Patient Name       | Type             | Arrival           | Status\n";
    std::cout << "------ | -------- | ------------------ | ---------------- | ----------------- | -------\n";
}

void EDO::printCase(const EmergencyCase &ec) const {
    std::cout << ec.caseID
              << "\t| " << ec.priorityLevel
              << "\t   | " << ec.patientName
              << " | " << ec.emergencyType
              << " | " << ec.arrivalTime
              << " | " << ec.status
              << '\n';
}

/* viewAll
   Read-only listing; does not modify ordering. */
void EDO::viewAll() const {
    if (isEmpty()) {
        std::cout << "[i] No pending cases.\n";
        return;
    }

    printHeader();
    for (int i = 0; i < size; ++i) {
        printCase(pq[i]);
    }
}

/* loadCSV
   CSV schema: CaseID,PatientName,EmergencyType,PriorityLevel,ArrivalTime,Status
   Behavior: Each parsed row is inserted via insertSorted() to maintain order.
   Notes: First line is treated as header and skipped. */
bool EDO::loadCSV(const std::string &path) {
    std::ifstream fin(path.c_str());
    if (!fin.is_open()) return false;

    std::string line;
    if (!std::getline(fin, line)) {
        fin.close();
        return false;
    }

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        EmergencyCase ec;

        std::getline(ss, token, ','); ec.caseID = std::atoi(token.c_str());
        std::getline(ss, ec.patientName, ',');
        std::getline(ss, ec.emergencyType, ',');
        std::getline(ss, token, ','); ec.priorityLevel = std::atoi(token.c_str());
        std::getline(ss, ec.arrivalTime, ',');
        std::getline(ss, ec.status, ',');

        if (!isFull()) insertSorted(ec);
    }

    fin.close();
    return true;
}

/* saveCSV
   Writes current in-memory order (priority-sorted) to CSV.
   Use before exit to persist user session data. */
bool EDO::saveCSV(const std::string &path) const {
    std::ofstream fout(path.c_str());
    if (!fout.is_open()) return false;

    fout << "CaseID,PatientName,EmergencyType,PriorityLevel,ArrivalTime,Status\n";

    for (int i = 0; i < size; ++i) {
        const EmergencyCase &ec = pq[i];
        fout << ec.caseID << ','
             << ec.patientName << ','
             << ec.emergencyType << ','
             << ec.priorityLevel << ','
             << ec.arrivalTime << ','
             << ec.status << "\n";
    }

    fout.close();
    return true;
}

/* emergencyDepartmentOfficerMenu
   Purpose: Menu-driven interface for the EDO module integrated with main system.
   Workflow covers: load → log/process/view → save.
   Note: nextCaseId auto-increments; priority input is clamped in logCase(). */
void emergencyDepartmentOfficerMenu() {
    EDO edo;
    edo.loadCSV(DATA_FILE);

    int choice = -1;
    int nextCaseId = 1001;

    while (true) {
        std::cout << "\n";
        std::cout << "=======================================================================\n";
        std::cout << "              EMERGENCY DEPARTMENT OFFICER MODULE                      \n";
        std::cout << "                   Priority-Based Case Management                      \n";
        std::cout << "=======================================================================\n";
        std::cout << "\nEMERGENCY DEPARTMENT OPTIONS:\n";
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << "  1. Log Emergency Case\n";
        std::cout << "     - Add a new emergency case with priority level\n";
        std::cout << "\n";
        std::cout << "  2. Process Most Critical Case\n";
        std::cout << "     - Handle the highest priority case first\n";
        std::cout << "\n";
        std::cout << "  3. View Pending Cases\n";
        std::cout << "     - Display all cases sorted by priority\n";
        std::cout << "\n";
        std::cout << "  4. Save & Return to Main Menu\n";
        std::cout << "     - Save current data and return\n";
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore(1024, '\n');

        if (choice == 1) {
            std::cout << "\n--- LOG NEW EMERGENCY CASE ---\n";
            std::string name, type, arrival, status;
            int pri = 0;

            std::cout << "Patient Name: ";
            std::getline(std::cin, name);
            std::cout << "Emergency Type (e.g., Trauma, Cardiac, Respiratory): ";
            std::getline(std::cin, type);
            std::cout << "Priority Level (1=Critical, 2=High, 3=Medium, 4=Low, 5=Minor): ";
            std::cin >> pri; std::cin.ignore(1024, '\n');
            std::cout << "Arrival Time (e.g., 2025-11-01 14:30): ";
            std::getline(std::cin, arrival);
            std::cout << "Status (Waiting/Processing/Resolved): ";
            std::getline(std::cin, status);

            if (edo.logCase(nextCaseId++, name, type, pri, arrival, status)) {
                std::cout << "\n[SUCCESS] Emergency case logged successfully!\n";
                std::cout << "Case ID: " << (nextCaseId - 1) << "\n";
            } else {
                std::cout << "\n[ERROR] Failed to log case - queue may be full.\n";
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            
        } else if (choice == 2) {
            std::cout << "\n--- PROCESS MOST CRITICAL CASE ---\n";
            EmergencyCase processed;
            if (edo.processMostCritical(processed)) {
                std::cout << "\n[PROCESSING]\n";
                std::cout << "Case ID       : " << processed.caseID << "\n";
                std::cout << "Patient Name  : " << processed.patientName << "\n";
                std::cout << "Emergency Type: " << processed.emergencyType << "\n";
                std::cout << "Priority Level: " << processed.priorityLevel << "\n";
                std::cout << "Arrival Time  : " << processed.arrivalTime << "\n";
                std::cout << "Status        : " << processed.status << "\n";
                std::cout << "\n[SUCCESS] Case processed successfully!\n";
            } else {
                std::cout << "\n[INFO] No cases available to process.\n";
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            
        } else if (choice == 3) {
            std::cout << "\n--- PENDING EMERGENCY CASES (Sorted by Priority) ---\n";
            edo.viewAll();
            
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            
        } else if (choice == 4) {
            std::cout << "\n--- SAVING DATA ---\n";
            if (edo.saveCSV(DATA_FILE)) {
                std::cout << "[SUCCESS] Emergency cases saved to '" << DATA_FILE << "'.\n";
            } else {
                std::cout << "[WARNING] Failed to save data to '" << DATA_FILE << "'.\n";
            }
            std::cout << "Returning to main menu...\n";
            break;
        } else {
            std::cout << "\n[ERROR] Invalid choice! Please enter a number between 1-4.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
}
