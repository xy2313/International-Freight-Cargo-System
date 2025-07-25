#pragma once
#include <string>
#include "InputValidator.h"

class ConsoleUI {
public:
    // Get a validated integer ID
    static int getIdInput(const std::string& prompt);

    // Get a validated destination name
    static std::string getDestinationInput(const std::string& prompt);

    // Get a validated time input (converts to HHMM format)
    static std::string getTimeInput(const std::string& prompt);

    // Get a validated cargo group ID
    static int getGroupIdInput(const std::string& prompt);

    // Get a validated freight type
    static FreightType getFreightTypeInput(const std::string& prompt);
};