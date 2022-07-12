#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <vector>

#include "core.h"

namespace Cataract {
class TcpScanner {
        public:
        TcpScanner();
        ~TcpScanner();

        ScanResult singleScan(const IPAddress addr, const uint16_t port) const;
        std::vector<Cataract::ScanResult> portSweep(const IPAddress addr, const std::vector<uint16_t> ports) const;
        
    };
}