#include "core.h"

#include <string.h>

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

Cataract::ScanResult::ScanResult(const IPAddress addr, const uint16_t port, const ScanStatus status) {
    _addr = addr;
    _port = port;
    _status = status;
}