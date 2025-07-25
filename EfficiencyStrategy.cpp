#include "EfficiencyStrategy.h"
#include "TimeWindowValidator.h"

using namespace std;

// Comparator for freight capacity (descending order)
bool compareFreightCapacity(const shared_ptr<Freight>& a, 
                           const shared_ptr<Freight>& b) {
    return a->getCapacity() > b->getCapacity();
}

// Comparator for cargo group size (descending order)
bool compareCargoGroup(const shared_ptr<Cargo>& a, 
                      const shared_ptr<Cargo>& b) {
    return a->getGroupId() > b->getGroupId();
}

void EfficiencyStrategy::schedule(FreightManager& fm, 
                                 CargoManager& cm, 
                                 Schedule& schedule) {
    auto freights = fm.getItems();
    auto cargos = cm.getItems();
    
    // Sort freights by capacity (largest first)
    sort(freights.begin(), freights.end(), compareFreightCapacity);
    
    // Sort cargos by group size (largest groups first)
    sort(cargos.begin(), cargos.end(), compareCargoGroup);
    
    // Create a vector to track assigned cargos
    vector<bool> assigned(cargos.size(), false);
    
    for (const auto& freight : freights) {
        // Reset freight load for scheduling
        freight->resetLoad();
        
        for (size_t i = 0; i < cargos.size(); i++) {
            if (assigned[i]) continue;
            
            auto& cargo = cargos[i];
            
            // Check if freight can carry this cargo
            if (freight->getDestination() == cargo->getDestination() &&
                TimeWindowValidator::isValid(freight->getTime(), cargo->getTime()) &&
                freight->canLoad()) {
                
                // Assign cargo to freight
                schedule.addAssignment(freight, cargo);
                freight->addCargo();
                assigned[i] = true;
                
                // Try to assign other cargos from the same group
                if (cargo->getGroupId() > 0) {
                    for (size_t j = i + 1; j < cargos.size(); j++) {
                        if (!assigned[j] && 
                            cargos[j]->getGroupId() == cargo->getGroupId() &&
                            freight->canLoad()) {
                            
                            schedule.addAssignment(freight, cargos[j]);
                            freight->addCargo();
                            assigned[j] = true;
                        }
                    }
                }
            }
        }
    }
    
    // Handle unassigned cargos (could be split to multiple freights)
    for (size_t i = 0; i < cargos.size(); i++) {
        if (assigned[i]) continue;
        
        auto& cargo = cargos[i];
        
        // Find any freight going to same destination with capacity
        for (const auto& freight : freights) {
            if (freight->getDestination() == cargo->getDestination() &&
                TimeWindowValidator::isValid(freight->getTime(), cargo->getTime()) &&
                freight->canLoad()) {
                
                schedule.addAssignment(freight, cargo);
                freight->addCargo();
                assigned[i] = true;
                break;
            }
        }
    }
}