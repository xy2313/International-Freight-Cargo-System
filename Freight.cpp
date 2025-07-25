#include <iostream>
#include <string>
#include "Freight.h"

using namespace std;

Freight::Freight(string id, string dest, string time, FreightType type)
    : Shipment(id, dest, time), type(type) {
    switch (type) {
    case FreightType::MiniMover: capacity = 2; break;
    case FreightType::CargoCruiser: capacity = 6; break;
    case FreightType::MegaCarrier: capacity = 12; break;
    }
}

void Freight::setType(FreightType newType) {
    type = newType;
    switch (type) {
    case FreightType::MiniMover: capacity = 2; break;
    case FreightType::CargoCruiser: capacity = 6; break;
    case FreightType::MegaCarrier: capacity = 12; break;
    }
}

void Freight::display() const {
    string typeStr;
    switch (type) {
    case FreightType::MiniMover: typeStr = "MiniMover"; break;
    case FreightType::CargoCruiser: typeStr = "CargoCruiser"; break;
    case FreightType::MegaCarrier: typeStr = "MegaCarrier"; break;
    }

    cout << "Freight ID: " << id
        << ", Destination: " << destination
        << ", Time: " << time
        << ", Type: " << typeStr
        << ", Load: " << currentLoad << "/" << capacity << endl;
}