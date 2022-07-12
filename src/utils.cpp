#include "utils.h"

#include <slog/slog.h>

std::vector<std::string> splitLine(const std::string &line, const char sep) {
    /** Takes a string, splits it into the strings separated by sep
     * and return a vector with of the resulting strings
     */
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
    /**
     *  Takes the ports string and returns a vector of all the ports to scan
     */
    
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
            try {
                range = {std::stoi(tempRange[0]), std::stoi(tempRange[0])};
            }
            catch(std::exception &e) {
                slog::error("Invalid port number");
                return false;
            }
        } else {
            // if it's a range we set the limits to the given numbers
            if (tempRange.size() > 2) {
                slog::warning("There is an invalid range\n"
                    "Port ranges should look like : x-y\n"
                    "only the first and second ranges will be considered");
                return false;
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
        /* if(range.second == 0) {
            // if it's a single port we push it as it is
            ports.push_back(range.first);
        }
        else {
            if (range.first > range.second) {
                slog::warning("the port ranges are in the wrong sense");
                std::swap(range.first, range.second);
            }
            // else we fill all the ports in the range
            for(int i = range.first; i <= range.second; i++) {
                ports.push_back(i);
            }
        } */
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
