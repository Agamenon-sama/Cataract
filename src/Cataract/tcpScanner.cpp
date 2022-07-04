#include "tcpScanner.h"

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