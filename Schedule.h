#pragma once
#include <vector>
#include <memory>
#include "Freight.h"
#include "Cargo.h"

class Schedule {
    std::vector<std::pair<std::shared_ptr<Freight>, std::shared_ptr<Cargo>>> assignments;

public:
    void addAssignment(std::shared_ptr<Freight> freight,
        std::shared_ptr<Cargo> cargo);
    void clear() { assignments.clear(); }
    void saveToFile(const std::string& filename = "schedule.txt") const;
    void display() const;

    const auto& getAssignments() const { return assignments; }
};