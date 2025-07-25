#include "FreightFactory.h"
#include "InputValidator.h"

std::shared_ptr<Shipment> FreightFactory::create(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4) return nullptr;

    std::string id = tokens[0];
    std::string dest = tokens[1];
    std::string time = InputValidator::normalizeTime(tokens[2]);
    FreightType type = InputValidator::parseFreightType(tokens[3]);

    return std::make_shared<Freight>(id, dest, time, type);
}