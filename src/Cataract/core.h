#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <string>

namespace Cataract {
    class IPAddress {
        public:
        IPAddress();
        IPAddress(std::string addr, sa_family_t addrType = AF_INET);

        sa_family_t getAddrType() const { return _addrHints.ai_family; }
        std::string getAddr() const { return _addr; }
        struct addrinfo getHints() const { return _addrHints; }

        void setAddr(std::string addr, sa_family_t addrType = AF_INET);

        private:
        // sa_family_t _addrType;
        struct addrinfo _addrHints;
        std::string _addr;
    };
}