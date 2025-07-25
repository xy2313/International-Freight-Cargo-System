#pragma once
#include <vector>
#include <memory>
#include "ShipmentFactory.h"
#include "Freight.h"

class FreightFactory : public ShipmentFactory {
public:
    std::shared_ptr<Shipment> create(const std::vector<std::string>& tokens) override;
};