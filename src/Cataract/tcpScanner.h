#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <vector>

#include "core.h"

namespace Cataract {
    /**
     * @brief TCP scanner
     * 
     * This class contains the methods that do the scanning
     */ 
    class TcpScanner {
        public:
        TcpScanner();
        ~TcpScanner();

        /**
         * @brief performs a single scan on a single host and single port
         * 
         * @param addr the address of the host to be scanned
         * @param port the port number to be scanned
         * @return a ScanResult Object
         */
        ScanResult singleScan(const IPAddress addr, const uint16_t port) const;

        /**
         * @brief scans multiple ports of a single host
         * 
         * @param addr the address of the host to be scanned
         * @param ports a vector of port numbers to be scanned
         * @return a vector of ScanResult Objects
         * 
         * This functions calls singleScan() internally
         * @sa singleScan
         */
        std::vector<Cataract::ScanResult> portSweep(const IPAddress addr, const std::vector<uint16_t> ports) const;
        
    };
}