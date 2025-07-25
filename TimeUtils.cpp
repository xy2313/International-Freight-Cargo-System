#include <stdexcept>
#include <algorithm>
#include <string>
#include "TimeUtils.h"

using namespace std;

int TimeUtils::toMinutes(const string& timeStr) {
    if (timeStr.length() != 4)
        throw invalid_argument("Invalid time format");

    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(2, 2));

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        throw out_of_range("Invalid time value");

    return hours * 60 + minutes;
}

string TimeUtils::normalizeTime(const string& input) {
    string clean = input;
    // Remove spaces
    clean.erase(remove(clean.begin(), clean.end(), ' '), clean.end());
    // Convert to lowercase
    transform(clean.begin(), clean.end(), clean.begin(),
        [](unsigned char c) { return tolower(c); });

    // Handle AM/PM formats
    size_t amPos = clean.find("am");
    size_t pmPos = clean.find("pm");
    bool hasAM = (amPos != string::npos);
    bool hasPM = (pmPos != string::npos);

    if (hasAM || hasPM) {
        // Extract time part
        string timePart = hasAM ? clean.substr(0, amPos) : clean.substr(0, pmPos);

        // Handle colon separator
        size_t colonPos = timePart.find(':');
        int hours = 0, minutes = 0;

        if (colonPos != string::npos) {
            hours = stoi(timePart.substr(0, colonPos));
            minutes = stoi(timePart.substr(colonPos + 1));
        }
        else if (timePart.length() >= 3) {
            // Handle formats like 730am, 1230pm
            hours = stoi(timePart.substr(0, timePart.length() - 2));
            minutes = stoi(timePart.substr(timePart.length() - 2));
        }
        else {
            throw invalid_argument("Invalid time format: " + input);
        }

        // Validate 12-hour format
        if (hours < 1 || hours > 12) {
            throw invalid_argument("Invalid hours in 12-hour format");
        }

        // Convert 12-hour to 24-hour format
        if (hasPM && hours < 12) hours += 12;
        if (hasAM && hours == 12) hours = 0;

        // Format as HHMM
        char buffer[5];
        snprintf(buffer, sizeof(buffer), "%02d%02d", hours, minutes);
        return string(buffer);
    }

    // Assume already in HHMM format
    if (clean.length() == 4 &&
        all_of(clean.begin(), clean.end(), ::isdigit)) {
        return clean;
    }

    throw invalid_argument("Invalid time format: " + input);
}