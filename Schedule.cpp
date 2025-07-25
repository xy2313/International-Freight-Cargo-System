#include "Schedule.h"
#include <fstream>
#include <iostream>

using namespace std;

void Schedule::addAssignment(shared_ptr<Freight> freight, 
                            shared_ptr<Cargo> cargo) {
    assignments.push_back(make_pair(freight, cargo));
}

void Schedule::saveToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& assignment : assignments) {
        file << assignment.first->getId() << ","
             << assignment.second->getId() << ","
             << assignment.first->getDestination() << ","
             << assignment.first->getTime() << "\n";
    }
    file.close();
}

void Schedule::display() const {
    if (assignments.empty()) {
        cout << "No assignments in schedule." << endl;
        return;
    }
    
    for (const auto& assignment : assignments) {
        cout << "Freight: " << assignment.first->getId();
        cout << " -> Cargo: " << assignment.second->getId();
        cout << " | Dest: " << assignment.first->getDestination();
        cout << " | Time: " << assignment.first->getTime() << endl;
    }
}