#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <string>
#include <vector>

/**
 * @brief all the network related tools
 * 
 * @author Chams Eddine Hachani (agamenon) <chams.eddine.hachanii@gmail.com>
 */

namespace Cataract {
    /**
     * @brief ip address abstraction
     * 
     * This class stores the ip address (v4 or v6) and handles address resolution
     */ 
    class IPAddress {
        public:
        IPAddress();
        IPAddress(std::string addr, sa_family_t addrType = AF_INET);

        sa_family_t getAddrType() const { return _addrHints.ai_family; } ///< @brief returns type of address v4 or v6
        std::string getAddr() const { return _addr; }
        std::string getIp() const { return _ip; }
        struct addrinfo getHints() const { return _addrHints; }

        void setAddr(std::string addr, sa_family_t addrType = AF_INET);

        private:
        struct addrinfo _addrHints; ///< @brief contains informations about the address like family...
        std::string _addr; ///< @brief address as inputed by the user (ip or domain name)
        std::string _ip; ///< @brief contains the resolved ip address from _addr else it contains "ip unknown"

        void _resolveName(); ///< @brief performs domain name resolution
    };

    /**
     * @brief possible status of the scanned port
     */
    enum class ScanStatus {
        Open = 0, Closed, SocketFailed, AddressNotFound
    };

    /**
     * @brief contains the result of scan
     */
    class ScanResult {
        public:
        ScanResult();
        ScanResult(const IPAddress addr, const uint16_t port, const ScanStatus status);

        ScanStatus getStatus() const { return _status; }
        uint16_t getPort() const { return _port; }
        IPAddress getAddress() const { return _addr; }
        bool isOpen() const { return !(bool)_status; } ///< @brief returns whether the port is accessible or not regardless of details

        private:
        IPAddress _addr; ///< @brief the scanned address
        uint16_t _port; ///< @brief the scanned port
        ScanStatus _status; ///< @brief the status of the port
    };

    /**
     * @brief determines port number from service name
     * 
     * @param service name of service like http, ssh, smtp...
     * @return on success returns the port number of the service else it returns 0
     */
    uint16_t servToPort(std::string service);
}
