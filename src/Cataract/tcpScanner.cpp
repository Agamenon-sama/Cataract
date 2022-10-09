#include "tcpScanner.h"

Cataract::TcpScanner::TcpScanner() {}
Cataract::TcpScanner::~TcpScanner() {}

Cataract::ScanResult Cataract::TcpScanner::singleScan(const IPAddress addr, const uint16_t port) const {
    // Making address
    struct addrinfo *addrsFound;
    struct addrinfo addrHint = addr.getHints(); // storing it here because I can't take the address of an rvalue
    if (getaddrinfo(addr.getAddr().c_str(), std::to_string(port).c_str(), &addrHint, &addrsFound) != 0) {
        return ScanResult(addr, port, ScanStatus::AddressNotFound);
    }

    // Making socket
    int sock = socket(addr.getHints().ai_family, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if(sock == -1) {
        return ScanResult(addr, port, ScanStatus::SocketFailed);
    }

    // Prepare select stuff
    fd_set fdWrite;
    FD_ZERO(&fdWrite); // init the fieldset
    FD_SET(sock, &fdWrite);
    struct timeval timeout {
        .tv_sec = 3,
        .tv_usec = 0
    };

    // Connecting
    ScanResult result;
    // Here I am assuming only 1 address is returned
    connect(sock, addrsFound->ai_addr, addrsFound->ai_addrlen);

    int selectRet = select(sock + 1, nullptr, &fdWrite, nullptr, &timeout);
    if (selectRet == -1) { // can't connect
        result = ScanResult(addr, port, ScanStatus::Closed); // todo: implement unexpected error
    }
    else if (selectRet == 0) { // timeout
        result = ScanResult(addr, port, ScanStatus::Closed); // todo: implement a timeout status
    } else {
        if (FD_ISSET(sock, &fdWrite)) {
            int sockOptError;
            socklen_t len = sizeof(sockOptError);

            getsockopt(sock, SOL_SOCKET, SO_ERROR, &sockOptError, &len);
            if (sockOptError) {
                result = ScanResult(addr, port, ScanStatus::Closed); // port closed
            }
            else {
                result = ScanResult(addr, port, ScanStatus::Open); // port open
            }
        }
        else {
            // todo: implement unexpected error
            result = ScanResult(addr, port, ScanStatus::Closed);
        }
    }

    freeaddrinfo(addrsFound);
    close(sock);
    return result;
    // if(!ret) {
    //     close(sock);
    //     return ScanResult(addr, port, ScanStatus::Open); // port open
    // } else {
    //     close(sock);
    //     return ScanResult(addr, port, ScanStatus::Closed); // port closed
    // }
}

std::vector<Cataract::ScanResult> Cataract::TcpScanner::portSweep(const IPAddress addr, const std::vector<uint16_t> ports) const {
    std::vector<Cataract::ScanResult> result;
    
    for(uint16_t port : ports) {
        result.push_back(singleScan(addr, port));
    }

    return result;
}