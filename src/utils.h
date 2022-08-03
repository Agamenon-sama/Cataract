#pragma once

#include <vector>
#include <string>

#include "Cataract/core.h"

/**
 * @brief splits a string according to the given separator
 * 
 * @param line string you want to split
 * @param sep separator that defines the splitting point. ';' by default
 * @return vector of the small strings
 */
std::vector<std::string> splitLine(const std::string &line, const char sep=';');

/**
 * @brief converts a string of ports to a vector of port numbers
 * 
 * @param portsArg string of the ports
 * @param ports vector of generated port number
 * @return true on success, false if the string is invalid
 * 
 * the port string looks something like "47,89-110,230,https"
 * ranges are separated by ',' and ranges are defines with lower and higher bounds separated by '-'
 * you can use service names like http,pop3... but they can't be the bounds of ranges
 * 
 * @note this function prints a warning to stderr if port ranges are in the wrong order
 */
bool argToPorts(const std::string &portsArg, std::vector<uint16_t> &ports);
