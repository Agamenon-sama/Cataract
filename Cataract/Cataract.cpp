#define SLOG_IMPLEMENTATION
#include <slog/slog.h>

#include "Cataract.h"

#include <string.h>

Cataract::TcpScanner::TcpScanner() {}
Cataract::TcpScanner::~TcpScanner() {}

bool Cataract::TcpScanner::singleScan(const IPAddress addr, const uint16_t port) const {
    // Making address
    struct addrinfo *addrsFound;
    struct addrinfo addrHint = addr.getHints(); // storing it here because I can't take the address of an rvalue
    if (getaddrinfo(addr.getAddr().c_str(), std::to_string(port).c_str(), &addrHint, &addrsFound) != 0) {
        return false;
    }

    // Making socket
    int sock = socket(addr.getHints().ai_family, SOCK_STREAM, 0);
    if(sock == -1) {
        slog::error("Failed to open socket for TcpScanner");
        return false;
    }

    // Connecting
    // Here I am assuming only 1 address is returned
    int ret = connect(sock, addrsFound->ai_addr, addrsFound->ai_addrlen);
    freeaddrinfo(addrsFound);
    if(!ret) {
        close(sock);
        return true; // port open
    } else {
        close(sock);
        return false; // port closed
    }
}

std::vector<std::pair<uint16_t, bool>> Cataract::TcpScanner::portSweep(const IPAddress addr, const std::vector<uint16_t> ports) const {
    std::vector<std::pair<uint16_t, bool>> result;
    
    for(uint16_t port : ports) {
        result.push_back({port, singleScan(addr, port)});
    }

    return result;
}



Cataract::IPAddress::IPAddress() {
    _addr = "";
    memset(&_addrHints, 0, sizeof(struct addrinfo));
}

Cataract::IPAddress::IPAddress(std::string addr, sa_family_t addrType) {
    memset(&_addrHints, 0, sizeof(struct addrinfo));
    _addr = addr;
    _addrHints.ai_family = addrType;
    _addrHints.ai_socktype = SOCK_STREAM;
    _addrHints.ai_protocol = IPPROTO_TCP;
}

void Cataract::IPAddress::setAddr(std::string addr, sa_family_t addrType) {
    _addr = addr;
    _addrHints.ai_family = addrType;
    _addrHints.ai_socktype = SOCK_STREAM;
    _addrHints.ai_protocol = IPPROTO_TCP;
}
