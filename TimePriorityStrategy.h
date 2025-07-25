#pragma once
#include <string>
#include "ISchedulingStrategy.h"

class TimePriorityStrategy : public ISchedulingStrategy {
public:
    void schedule(FreightManager& fm, CargoManager& cm, Schedule& schedule) override;
    std::string getName() const override { return "Time-Priority Scheduling"; }
};