#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <slog/slog.h>

#include <string>
#include <vector>

namespace Cataract {
    class IPAddress {
        public:
        IPAddress(std::string addr, sa_family_t addrType = AF_INET);

        sa_family_t getAddrType() const { return _addrType; }

        private:
        sa_family_t _addrType;
        std::string _addr;
    };

    class TcpScanner {
        public:
        TcpScanner();
        ~TcpScanner();

        bool singleScan(IPAddress addr, uint16_t port) const;
        std::vector<std::pair<uint16_t, bool>> portSwip(IPAddress addr, std::vector<uint16_t> ports) const;
        
        private:
        int _socket;
    };
}