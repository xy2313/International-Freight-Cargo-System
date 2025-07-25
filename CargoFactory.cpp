#include "CargoFactory.h"
#include "InputValidator.h"

std::shared_ptr<Shipment> CargoFactory::create(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4) return nullptr;

    std::string id = tokens[0];
    std::string dest = tokens[1];
    std::string time = InputValidator::normalizeTime(tokens[2]);
    int groupId = std::stoi(tokens[3]);

    return std::make_shared<Cargo>(id, dest, time, groupId);
}