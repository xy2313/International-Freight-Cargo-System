#include <iostream>
#include <memory>
#include <algorithm>
#include "FreightManager.h"
#include "CargoManager.h"
#include "Schedule.h"
#include "TimePriorityStrategy.h"
#include "EfficiencyStrategy.h"
#include "ConsoleUI.h"
#include "InputValidator.h"

using namespace std;

string cleanPath(string path) {
    const string trimChars = " \t\n\r\"\'";
    if (path.empty()) return path;
    size_t start = path.find_first_not_of(trimChars);
    size_t end = path.find_last_not_of(trimChars);
    if (start == string::npos) return "";
    return path.substr(start, end - start + 1);
}

void displayUnmatched(const FreightManager& fm, const CargoManager& cm, const Schedule& schedule) {
    // Get all assigned cargo IDs
    vector<string> assignedCargoIds;
    for (const auto& assignment : schedule.getAssignments()) {
        assignedCargoIds.push_back(assignment.second->getId());
    }

    // Display freights at full capacity
    std::cout << "\n=== FREIGHTS AT FULL CAPACITY ===" << endl;
    bool foundFullCapacity = false;
    for (const auto& freight : fm.getItems()) {
        if (freight->isFull()) {
            freight->display();
            foundFullCapacity = true;
        }
    }
    if (!foundFullCapacity) std::cout << "No freights at full capacity." << endl;

    // Display freights not at full capacity
    std::cout << "\n=== FREIGHTS NOT AT FULL CAPACITY ===" << endl;
    bool foundNotFullCapacity = false;
    for (const auto& freight : fm.getItems()) {
        if (!freight->isFull()) {
            freight->display();
            foundNotFullCapacity = true;
        }
    }
    if (!foundNotFullCapacity) std::cout << "All freights are fully utilized." << endl;

    // Display unassigned cargos
    std::cout << "\n=== UNASSIGNED CARGOS ===" << endl;
    bool foundUnassigned = false;
    for (const auto& cargo : cm.getItems()) {
        if (find(assignedCargoIds.begin(), assignedCargoIds.end(), cargo->getId()) == assignedCargoIds.end()) {
            cargo->display();
            foundUnassigned = true;
        }
    }
    if (!foundUnassigned) std::cout << "All cargos have been assigned." << endl;
}

int main() {
    cout << "===== INTERNATIONAL FREIGHT CARGO SYSTEM =====" << endl;

    string freightPath, cargoPath;
    FreightManager fm("");
    CargoManager cm("");

    // Get freight data file path
    while (true) {
        cout << "Enter freight data file path: ";
        getline(cin, freightPath);
        freightPath = cleanPath(freightPath);
        if (freightPath.empty()) freightPath = "freightData.txt";

        fm.setFilename(freightPath);
        if (fm.loadFile()) break;
        cout << "Error opening file: " << freightPath << endl;
    }

    // Get cargo data file path
    while (true) {
        cout << "Enter cargo data file path: ";
        getline(cin, cargoPath);
        cargoPath = cleanPath(cargoPath);
        if (cargoPath.empty()) cargoPath = "cargoData.txt";

        cm.setFilename(cargoPath);
        if (cm.loadFile()) break;
        cout << "Error opening file: " << cargoPath << endl;
    }

    Schedule schedule;

    // Main application loop
    while (true) {
        cout << "\n===== MAIN MENU ====="
            << "\n1. Generate Schedule"
            << "\n2. Freight Management"
            << "\n3. Cargo Management"
            << "\n4. View Current Schedule"
            << "\n5. View System Reports"
            << "\n0. Exit & Save Data"
            << "\nEnter choice: ";

        int mainChoice;
        cin >> mainChoice;
        cin.ignore(); // Clear newline

        if (mainChoice == 0) break;

        switch (mainChoice) {
        case 1: { // Generate Schedule
            cout << "\n===== SCHEDULING OPTIONS ====="
                << "\n1. Time-Priority (Ensure timely delivery)"
                << "\n2. Efficiency (Maximize freight utilization)"
                << "\n0. Back"
                << "\nEnter choice: ";

            int scheduleChoice;
            cin >> scheduleChoice;
            cin.ignore();

            if (scheduleChoice == 0) break;

            unique_ptr<ISchedulingStrategy> strategy;
            string strategyName;

            if (scheduleChoice == 1) {
                strategy = make_unique<TimePriorityStrategy>();
                strategyName = "Time-Priority";
            }
            else if (scheduleChoice == 2) {
                strategy = make_unique<EfficiencyStrategy>();
                strategyName = "Efficiency";
            }
            else {
                cout << "Invalid choice." << endl;
                break;
            }

            // Reset freight loads before scheduling
            for (auto& freight : fm.getItems()) {
                freight->resetLoad();
            }

            schedule.clear();
            strategy->schedule(fm, cm, schedule);
            schedule.saveToFile();

            cout << "\nSchedule generated using " << strategyName << " strategy." << endl;
            cout << "Total assignments: " << schedule.getAssignments().size() << endl;
            cout << "Saved to schedule.txt" << endl;

            break;
        }
        case 2: { // Freight Management
            while (true) {
                cout << "\n===== FREIGHT MANAGEMENT ====="
                    << "\n1. Add Freight"
                    << "\n2. Edit Freight"
                    << "\n3. Delete Freight"
                    << "\n4. Display All Freights"
                    << "\n5. Save Changes"
                    << "\n0. Back"
                    << "\nEnter choice: ";

                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 0) break;

                switch (choice) {
                case 1: { // Add Freight
                    int idNum = ConsoleUI::getIdInput("Enter Freight ID number: ");
                    string place = ConsoleUI::getDestinationInput("Enter Destination: ");
                    string time = ConsoleUI::getTimeInput("Enter Time (HHMM or 7:30am): ");
                    FreightType type = ConsoleUI::getFreightTypeInput("Enter Type (MiniMover, CargoCruiser, MegaCarrier): ");

                    try {
                        fm.addItem(idNum, place, time, type);
                        cout << "Freight added successfully." << endl;
                    }
                    catch (const runtime_error& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 2: { // Edit Freight
                    int idNum = ConsoleUI::getIdInput("Enter Freight ID number to edit: ");
                    string place = ConsoleUI::getDestinationInput("Enter new Destination: ");
                    string time = ConsoleUI::getTimeInput("Enter new Time (HHMM or 7:30am): ");
                    FreightType type = ConsoleUI::getFreightTypeInput("Enter new Type (MiniMover, CargoCruiser, MegaCarrier): ");

                    if (fm.editItem(idNum, place, time, type)) {
                        cout << "Freight updated successfully." << endl;
                    }
                    else {
                        cout << "Freight not found." << endl;
                    }
                    break;
                }
                case 3: { // Delete Freight
                    int idNum = ConsoleUI::getIdInput("Enter Freight ID number to delete: ");

                    if (fm.deleteItem(idNum)) {
                        cout << "Freight deleted successfully." << endl;
                    }
                    else {
                        cout << "Freight not found." << endl;
                    }
                    break;
                }
                case 4: // Display All
                    fm.displayAll();
                    break;
                case 5: // Save Changes
                    fm.writeFile();
                    cout << "Freight data saved to " << freightPath << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                }
            }
            break;
        }
        case 3: { // Cargo Management
            while (true) {
                cout << "\n===== CARGO MANAGEMENT ====="
                    << "\n1. Add Cargo"
                    << "\n2. Edit Cargo"
                    << "\n3. Delete Cargo"
                    << "\n4. Display All Cargos"
                    << "\n5. Save Changes"
                    << "\n0. Back"
                    << "\nEnter choice: ";

                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 0) break;

                switch (choice) {
                case 1: { // Add Cargo
                    int idNum = ConsoleUI::getIdInput("Enter Cargo ID number: ");
                    string place = ConsoleUI::getDestinationInput("Enter Destination: ");
                    string time = ConsoleUI::getTimeInput("Enter Time (HHMM or 7:30am): ");
                    int groupId = ConsoleUI::getGroupIdInput("Enter Group ID (0 if none): ");

                    try {
                        cm.addItem(idNum, place, time, groupId);
                        cout << "Cargo added successfully." << endl;
                    }
                    catch (const runtime_error& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 2: { // Edit Cargo
                    int idNum = ConsoleUI::getIdInput("Enter Cargo ID number to edit: ");
                    string place = ConsoleUI::getDestinationInput("Enter new Destination: ");
                    string time = ConsoleUI::getTimeInput("Enter new Time (HHMM or 7:30am): ");
                    int groupId = ConsoleUI::getGroupIdInput("Enter new Group ID (0 if none): ");

                    if (cm.editItem(idNum, place, time, groupId)) {
                        cout << "Cargo updated successfully." << endl;
                    }
                    else {
                        cout << "Cargo not found." << endl;
                    }
                    break;
                }
                case 3: { // Delete Cargo
                    int idNum = ConsoleUI::getIdInput("Enter Cargo ID number to delete: ");

                    if (cm.deleteItem(idNum)) {
                        cout << "Cargo deleted successfully." << endl;
                    }
                    else {
                        cout << "Cargo not found." << endl;
                    }
                    break;
                }
                case 4: // Display All
                    cm.displayAll();
                    break;
                case 5: // Save Changes
                    cm.writeFile();
                    cout << "Cargo data saved to " << cargoPath << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                }
            }
            break;
        }
        case 4: // View Current Schedule
            if (schedule.getAssignments().empty()) {
                cout << "No schedule generated yet. Please generate a schedule first." << endl;
            }
            else {
                cout << "\n===== CURRENT SCHEDULE =====" << endl;
                schedule.display();
            }
            break;

        case 5: // System Reports
            if (schedule.getAssignments().empty()) {
                cout << "No schedule generated yet. Please generate a schedule first." << endl;
            }
            else {
                displayUnmatched(fm, cm, schedule);
            }
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Save data before exiting
    fm.writeFile();
    cm.writeFile();
    cout << "\nData saved to files:" << endl;
    cout << "  Freights: " << freightPath << endl;
    cout << "  Cargos: " << cargoPath << endl;
    cout << "Exiting system..." << endl;

    return 0;
}