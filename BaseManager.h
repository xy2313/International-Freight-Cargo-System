#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include "ShipmentFactory.h"
#include "Cargo.h"
#include "Freight.h"

template <typename T>
class BaseManager {
protected:
    std::vector<std::shared_ptr<T>> items;
    std::string filename;
    std::unique_ptr<ShipmentFactory> factory;

    virtual std::string formatId(int idNum) const = 0;

public:
    BaseManager(std::string filename, std::unique_ptr<ShipmentFactory> factory)
        : filename(filename), factory(std::move(factory)) {
    }

    virtual ~BaseManager() = default;

    void setFilename(std::string newFilename) { filename = newFilename; }

    bool loadFile() {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        items.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (auto item = std::dynamic_pointer_cast<T>(factory->create(tokens))) {
                items.push_back(item);
            }
        }
        file.close();
        return true;
    }

    void writeFile() const {
        std::ofstream file(filename);
        for (const auto& item : items) {
            file << item->getId() << ","
                << item->getDestination() << ","
                << item->getTime() << ",";

            if (auto cargo = std::dynamic_pointer_cast<Cargo>(item)) {
                file << cargo->getGroupId();
            }
            else if (auto freight = std::dynamic_pointer_cast<Freight>(item)) {
                switch (freight->getType()) {
                case FreightType::MiniMover: file << "MiniMover"; break;
                case FreightType::CargoCruiser: file << "CargoCruiser"; break;
                case FreightType::MegaCarrier: file << "MegaCarrier"; break;
                }
            }
            file << "\n";
        }
        file.close();
    }

    void displayAll() const {
        if (items.empty()) {
            std::cout << "No items found." << std::endl;
            return;
        }
        for (const auto& item : items) {
            item->display();
        }
    }

    const std::vector<std::shared_ptr<T>>& getItems() const { return items; }

    // CRUD Operations
    void addItem(std::shared_ptr<T> item) {
        // Check for duplicate ID
        auto it = std::find_if(items.begin(), items.end(),
            [&item](const auto& i) { return i->getId() == item->getId(); });
        if (it != items.end()) {
            throw std::runtime_error("ID " + item->getId() + " already exists");
        }
        items.push_back(item);
    }

    bool editItem(const std::string& id,
        std::function<void(std::shared_ptr<T>)> editFunction) {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const auto& item) { return item->getId() == id; });

        if (it != items.end()) {
            editFunction(*it);
            return true;
        }
        return false;
    }

    bool deleteItem(const std::string& id) {
        auto it = std::remove_if(items.begin(), items.end(),
            [&id](const auto& item) { return item->getId() == id; });

        if (it != items.end()) {
            items.erase(it, items.end());
            return true;
        }
        return false;
    }

    bool idExists(const std::string& id) const {
        return std::any_of(items.begin(), items.end(),
            [&id](const auto& item) { return item->getId() == id; });
    }
};