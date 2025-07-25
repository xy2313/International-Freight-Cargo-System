#pragma once
#include <string>
#include "Shipment.h"

class Cargo : public Shipment {
    int groupId;

public:
    Cargo(std::string id = "",
        std::string dest = "",
        std::string time = "",
        int groupId = 0);

    // Getters
    int getGroupId() const { return groupId; }

    // Setters
    void setGroupId(int group) { groupId = group; }

    void display() const override;
};