#include "utils.h"

#include "Cataract/core.h"

#include <slog/slog.h>

std::vector<std::string> splitLine(const std::string &line, const char sep) {
    std::vector<std::string> returnValue;
    std::string temp;

    for(size_t i = 0; i < line.size(); i++) {
        if(line[i] != sep) {
            temp.push_back(line[i]);
        } else {
            if(!temp.empty()) {
                returnValue.push_back(temp);
                temp = "";
            }
        }
    }
    returnValue.push_back(temp);

    return returnValue;
}

bool argToPorts(const std::string &portsArg, std::vector<uint16_t> &ports) {
    // ==================
    // determining ranges
    // ==================
    // holds the limits of the port ranges
    std::vector<std::pair<uint16_t, uint16_t>> ranges;

    // portsArg: "a-b,c-d,e-f"
    auto commaSeparated = splitLine(portsArg, ',');
    // commaSeparated: {"a-b", "c-d", "e-f"}
    for (auto strRange : commaSeparated) {
        // get limits of range
        auto tempRange = splitLine(strRange, '-');
        // turn range to std::pair
        std::pair<uint16_t, uint16_t> range;

        if (tempRange.size() == 1) {
            // if it's a single port number we set the other limit to 0
            std::string portStr = tempRange[0];
            try {
                range = {std::stoi(tempRange[0]), std::stoi(tempRange[0])};
            }
            catch(std::exception &e) {
                uint16_t port = htons(Cataract::servToPort(portStr));
                if (port != 0) {
                    range = {port, port};
                }
                else {
                    slog::error("Invalid port number");
                    return false;
                }
            }
        } else {
            // if it's a range we set the limits to the given numbers
            if (tempRange.size() > 2) {
                slog::warning("There is an invalid range\n"
                    "Port ranges should look like : x-y\n"
                    "only the first and second ranges will be considered");
            }
            try {
                range = {std::stoi(tempRange[0]), std::stoi(tempRange[1])};
            }
            catch(std::exception &e) {
                slog::error("Invalid port number");
                return false;
            }
        }
        ranges.push_back(range);
    }

    // ==================
    // use ranges to get a vector of ports
    // ==================
    for(auto range : ranges) {
        if (range.first > range.second) {
            slog::warning("the port ranges are in the wrong sense");
            std::swap(range.first, range.second);
        }
        // else we fill all the ports in the range
        for(int i = range.first; i <= range.second; i++) {
            ports.push_back(i);
        }
    }

    return true;
}
