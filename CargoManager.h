#pragma once
#include "BaseManager.h"
#include "CargoFactory.h"

class CargoManager : public BaseManager<Cargo> {
private:
    std::string formatId(int idNum) const override {
        return "C" + (idNum < 10 ? std::string("0") : std::string("")) + std::to_string(idNum);
    }

public:
    CargoManager(std::string filename)
        : BaseManager(filename, std::make_unique<CargoFactory>()) {
    }

    void addItem(int idNum, std::string dest, std::string time, int groupId = 0) {
        std::string id = formatId(idNum);
        if (idExists(id)) {
            throw std::runtime_error("Cargo ID " + id + " already exists");
        }
        auto cargo = std::make_shared<Cargo>(id, dest, time, groupId);
        BaseManager::addItem(cargo);
    }

    bool editItem(int idNum, std::string newDest, std::string newTime, int newGroupId) {
        std::string id = formatId(idNum);
        return BaseManager::editItem(id, [&](auto cargo) {
            cargo->setDestination(newDest);
            cargo->setTime(newTime);
            cargo->setGroupId(newGroupId);
            });
    }

    bool deleteItem(int idNum) {
        std::string id = formatId(idNum);
        return BaseManager::deleteItem(id);
    }

    std::shared_ptr<Cargo> getItem(int idNum) {
        std::string id = formatId(idNum);
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const auto& item) { return item->getId() == id; });
        return (it != items.end()) ? *it : nullptr;
    }
};