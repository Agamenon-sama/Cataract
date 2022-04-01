#define SLOG_IMPLEMENTATION
#include <slog/slog.h>

#include "Cataract.h"

Cataract::TcpScanner::TcpScanner() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if(_socket == -1) {
        slog::error("Failed to open socket for TcpScanner");
    }
}

Cataract::TcpScanner::~TcpScanner() {
    close(_socket);
}

bool Cataract::TcpScanner::singleScan(IPAddress addr, uint16_t port) const {
    // Making address
    struct sockaddr_in sAddr;
    sAddr.sin_family = addr.getAddrType();
    sAddr.sin_port = htons(port);
    sAddr.sin_addr.s_addr = INADDR_ANY;
    // sAddr.sin_addr.s_addr = inet_addr("107.161.19.243"); // 107.161.19.243 = lainchan.org

    // Connecting
    int ret = connect(_socket, (struct sockaddr*) &sAddr, sizeof(sAddr));
    if(!ret) {
        return true; // port open
    } else {
        return false; // port closed
    }
}

std::vector<std::pair<uint16_t, bool>> Cataract::TcpScanner::portSwip(IPAddress addr, std::vector<uint16_t> ports) const {
    std::vector<std::pair<uint16_t, bool>> result;
    
    for(uint16_t port : ports) {
        result.push_back({port, singleScan(addr, port)});
    }

    return result;
}



Cataract::IPAddress::IPAddress(std::string addr, sa_family_t addrType) {
    _addr = addr;
    _addrType = addrType;
}