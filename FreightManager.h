#pragma once
#include "BaseManager.h"
#include "FreightFactory.h"

class FreightManager : public BaseManager<Freight> {
private:
    std::string formatId(int idNum) const override {
        return "F" + (idNum < 10 ? std::string("0") : std::string("")) + std::to_string(idNum);
    }

public:
    FreightManager(std::string filename)
        : BaseManager(filename, std::make_unique<FreightFactory>()) {
    }

    void addItem(int idNum, std::string dest, std::string time, FreightType type) {
        std::string id = formatId(idNum);
        if (idExists(id)) {
            throw std::runtime_error("Freight ID " + id + " already exists");
        }
        auto freight = std::make_shared<Freight>(id, dest, time, type);
        BaseManager::addItem(freight);
    }

    bool editItem(int idNum, std::string newDest, std::string newTime, FreightType newType) {
        std::string id = formatId(idNum);
        return BaseManager::editItem(id, [&](auto freight) {
            freight->setDestination(newDest);
            freight->setTime(newTime);
            freight->setType(newType);
            });
    }

    bool deleteItem(int idNum) {
        std::string id = formatId(idNum);
        return BaseManager::deleteItem(id);
    }

    std::shared_ptr<Freight> getItem(int idNum) {
        std::string id = formatId(idNum);
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const auto& item) { return item->getId() == id; });
        return (it != items.end()) ? *it : nullptr;
    }
};