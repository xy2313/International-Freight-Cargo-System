#pragma once
#include <string>

class TimeUtils {
public:
    static int toMinutes(const std::string& timeStr);
    static std::string normalizeTime(const std::string& input);
};