#pragma once
#include <string>
#include "FreightManager.h"
#include "CargoManager.h"
#include "Schedule.h"

class ISchedulingStrategy {
public:
    virtual ~ISchedulingStrategy() = default;
    virtual void schedule(FreightManager& fm, 
                          CargoManager& cm, 
                          Schedule& schedule) = 0;
    virtual std::string getName() const = 0;
};