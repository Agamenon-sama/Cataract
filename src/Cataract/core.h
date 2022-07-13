#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <string>
#include <vector>

namespace Cataract {
    class IPAddress {
        public:
        IPAddress();
        IPAddress(std::string addr, sa_family_t addrType = AF_INET);

        sa_family_t getAddrType() const { return _addrHints.ai_family; }
        std::string getAddr() const { return _addr; }
        std::string getIp() const { return _ip; }
        struct addrinfo getHints() const { return _addrHints; }

        void setAddr(std::string addr, sa_family_t addrType = AF_INET);

        private:
        struct addrinfo _addrHints;
        std::string _addr;
        std::string _ip;

        void _resolveName();
    };

    enum class ScanStatus {
        Open = 0, Closed, SocketFailed, AddressNotFound
    };

    class ScanResult {
        public:
        ScanResult();
        ScanResult(const IPAddress addr, const uint16_t port, const ScanStatus status);

        ScanStatus getStatus() const { return _status; }
        uint16_t getPort() const { return _port; }
        IPAddress getAddress() const { return _addr; }
        bool isOpen() const { return !(bool)_status; }

        private:
        IPAddress _addr;
        uint16_t _port;
        ScanStatus _status;
    };

    uint16_t servToPort(std::string service);
}
