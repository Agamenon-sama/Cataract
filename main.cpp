#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Cataract/Cataract.h"

#include <slog/slog.h>

static std::vector<std::string> parseLine(const std::string &line, const char sep=';') {
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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        slog::error("Usage example : cataract ports 45-78,5,8");
        return 1;
    }

    if (std::string(argv[1]) == "port") {
        // get comma Separated ranges
        auto commaSeparated = parseLine(argv[2], ',');
        std::vector<std::pair<uint16_t, uint16_t>> ranges;

        for (auto strRange : commaSeparated) {
            // get limits of range
            auto tempRange = parseLine(strRange, '-');
            // turn range to std::pair
            std::pair<uint16_t, uint16_t> range;

            // TODO: handle invalid inputs like
            // - non numbers
            // - invalid numbers
            // - first limit larger than second limit (preferably swap)
            if (tempRange.size() == 1) {
                // if it's a single port number we set the other limit to 0
                range = {std::stoi(tempRange[0]), 0};
            } else {
                // if it's a range we set the limits to the given numbers
                if (tempRange.size() > 2) {
                    slog::warning("There is an invalid range\n"
                        "Port ranges should look like : x-y\n"
                        "only the first and second ranges will be considered");
                }
                range = {std::stoi(tempRange[0]), std::stoi(tempRange[1])};
            }
            ranges.push_back(range);
        }

        Cataract::TcpScanner scanner;
        Cataract::IPAddress addr("127.0.0.1");

        std::vector<uint16_t> ports;
        for(auto range : ranges) {
            if(range.second == 0) {
                // if it's a single port we push it as it is
                ports.push_back(range.first);
            }
            else {
                // else we fill all the ports in the range
                for(int i = range.first; i <= range.second; i++) {
                    ports.push_back(i);
                }
            }
        }

        // We scan and print the results
        auto scanResult = scanner.portSwip(addr, ports);
        for(auto test : scanResult) {
            if(test.second) { // second holds the test result
                std::cout << "Port " << test.first << "/tcp is \e[32mopen\e[0m\n";
            } else {
                std::cout << "Port " << test.first << "/tcp is \e[31mclosed\e[0m\n";
            }
        }
    }

    return 0;
}
