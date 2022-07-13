#pragma once

#include <vector>
#include <string>

#include "Cataract/core.h"

std::vector<std::string> splitLine(const std::string &line, const char sep=';');
bool argToPorts(const std::string &portsArg, std::vector<uint16_t> &ports);
