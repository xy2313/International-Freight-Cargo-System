#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Shipment.h"

class ShipmentFactory {
public:
    virtual ~ShipmentFactory() = default;
    virtual std::shared_ptr<Shipment> create(const std::vector<std::string>& tokens) = 0;
};