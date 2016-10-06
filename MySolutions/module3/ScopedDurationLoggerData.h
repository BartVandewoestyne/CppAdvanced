#ifndef SCOPED_DURATION_LOGGER_DATA
#define SCOPED_DURATION_LOGGER_DATA

#include <string>
#include <vector>
#include <map>

class ScopedDurationLoggerData {

public:
    void operator() (double seconds, const std::string& tag)
    {
        values[tag].push_back(seconds);
    }

public:
    static std::map<std::string, std::vector<double>> values;

};

std::map<std::string, std::vector<double>> ScopedDurationLoggerData::values;

#endif // SCOPED_DURATION_LOGGER_DATA
