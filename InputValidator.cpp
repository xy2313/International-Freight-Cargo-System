#include <algorithm>
#include <stdexcept>
#include <string>
#include "InputValidator.h"
#include "TimeUtils.h"

using namespace std;

int InputValidator::validateId(const string& input) {
    if (input.empty()) throw invalid_argument("ID cannot be empty");

    // Check if all characters are digits
    if (!all_of(input.begin(), input.end(), ::isdigit)) {
        throw invalid_argument("ID must contain only digits");
    }

    try {
        int id = stoi(input);
        if (id < 0) throw invalid_argument("ID cannot be negative");
        return id;
    }
    catch (...) {
        throw invalid_argument("Invalid ID format");
    }
}

string InputValidator::validateDestination(const string& input) {
    if (input.empty()) throw invalid_argument("Destination cannot be empty");

    // Check for valid characters
    for (char c : input) {
        if (!isalpha(c) && c != ' ' && c != '\'' && c != '-') {
            throw invalid_argument("Invalid character in destination name");
        }
    }
    return input;
}

string InputValidator::validateTime(const string& input) {
    string clean = input;
    // Remove spaces
    clean.erase(remove(clean.begin(), clean.end(), ' '), clean.end());

    if (clean.empty()) throw invalid_argument("Time cannot be empty");

    // Check if it's in HHMM format (4 digits)
    if (clean.length() == 4 && all_of(clean.begin(), clean.end(), ::isdigit)) {
        int hours = stoi(clean.substr(0, 2));
        int minutes = stoi(clean.substr(2, 2));

        if (hours < 0 || hours > 23) throw invalid_argument("Hours must be 00-23");
        if (minutes < 0 || minutes > 59) throw invalid_argument("Minutes must be 00-59");

        return clean;
    }

    // Check for AM/PM format
    if (clean.find("am") != string::npos || clean.find("pm") != string::npos) {
        return clean; // Will be normalized later
    }

    throw invalid_argument("Invalid time format. Use HHMM or H:MMam/pm");
}

int InputValidator::validateGroupId(const string& input) {
    if (input.empty()) return 0; // Default to no group

    try {
        int group = stoi(input);
        if (group < 0) throw invalid_argument("Group ID cannot be negative");
        return group;
    }
    catch (...) {
        throw invalid_argument("Group ID must be a number");
    }
}

FreightType InputValidator::parseFreightType(const string& input) {
    string type = input;
    // Convert to lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "minimover") return FreightType::MiniMover;
    if (type == "cargocruiser") return FreightType::CargoCruiser;
    if (type == "megacarrier") return FreightType::MegaCarrier;

    throw invalid_argument("Unknown freight type: " + input);
}

string InputValidator::normalizeTime(const string& input) {
    return TimeUtils::normalizeTime(input);
}