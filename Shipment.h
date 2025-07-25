#pragma once
#include <string>

enum class FreightType;

class Shipment {
protected:
    std::string id;
    std::string destination;
    std::string time;

public:
    Shipment(std::string id = "",
        std::string dest = "",
        std::string time = "");
    virtual ~Shipment() = default;

    virtual void display() const = 0;

    // Getters
    std::string getId() const { return id; }
    std::string getDestination() const { return destination; }
    std::string getTime() const { return time; }

    // Setters
    void setId(std::string id) { this->id = id; }
    void setDestination(std::string dest) { destination = dest; }
    void setTime(std::string time) { this->time = time; }
};