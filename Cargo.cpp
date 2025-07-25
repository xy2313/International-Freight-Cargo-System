#include <iostream>
#include <string>
#include "Cargo.h"

using namespace std;

Cargo::Cargo(string id, string dest, string time, int groupId)
    : Shipment(id, dest, time), groupId(groupId) {
}

void Cargo::display() const {
    cout << "Cargo ID: " << id
        << ", Destination: " << destination
        << ", Time: " << time
        << ", Group: " << groupId << endl;
}