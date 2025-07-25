#include <string>
#include "TimeWindowValidator.h"
#include "TimeUtils.h"

bool TimeWindowValidator::isValid(const std::string& freightTime, 
                                  const std::string& cargoTime) {
    int freightMinutes = TimeUtils::toMinutes(freightTime);
    int cargoMinutes = TimeUtils::toMinutes(cargoTime);
    
    // Cargo should arrive no more than 15 minutes early
    return (cargoMinutes - freightMinutes) <= 15 && 
           (cargoMinutes - freightMinutes) >= 0;
}