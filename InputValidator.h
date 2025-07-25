#pragma once
#include <string>
#include "Freight.h"
#include "Cargo.h"

class InputValidator {
public:
    // Validate ID number (non-negative integer)
    static int validateId(const std::string& input);

    // Validate destination name (alphabets and spaces only)
    static std::string validateDestination(const std::string& input);

    // Validate time format (accepts HHMM or H:MMam/pm formats)
    static std::string validateTime(const std::string& input);

    // Validate group ID (non-negative integer)
    static int validateGroupId(const std::string& input);

    // Parse freight type string to enum
    static FreightType parseFreightType(const std::string& input);

    // Normalize time to HHMM format
    static std::string normalizeTime(const std::string& input);
};