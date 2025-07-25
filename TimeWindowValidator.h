#pragma once
#include <string>

class TimeWindowValidator {
public:
    static bool isValid(const std::string& freightTime, 
                        const std::string& cargoTime);
};