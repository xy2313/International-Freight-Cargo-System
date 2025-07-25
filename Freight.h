#pragma once
#include <string>
#include "Shipment.h"

enum class FreightType { MiniMover, CargoCruiser, MegaCarrier };

class Freight : public Shipment {
    FreightType type;
    int capacity = 0;
    int currentLoad = 0;

public:
    Freight(std::string id = "",
        std::string dest = "",
        std::string time = "",
        FreightType type = FreightType::MiniMover);

    // Getters
    FreightType getType() const { return type; }
    int getCapacity() const { return capacity; }
    int getCurrentLoad() const { return currentLoad; }
    bool isFull() const { return currentLoad >= capacity; }

    // Setters
    void setType(FreightType newType);

    // Operations
    bool canLoad() const { return currentLoad < capacity; }
    void addCargo() { if (canLoad()) currentLoad++; }
    void resetLoad() { currentLoad = 0; }

    void display() const override;
};