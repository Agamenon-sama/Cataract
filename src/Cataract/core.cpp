#include "core.h"

#include <string.h>

Cataract::IPAddress::IPAddress() {
    _addr = "";
    memset(&_addrHints, 0, sizeof(struct addrinfo));
}

Cataract::IPAddress::IPAddress(std::string addr, sa_family_t addrType) {
    memset(&_addrHints, 0, sizeof(struct addrinfo));
    _addr = addr;
    _addrHints.ai_flags = AI_CANONNAME;
    _addrHints.ai_family = addrType;
    _addrHints.ai_socktype = SOCK_STREAM;
    _addrHints.ai_protocol = IPPROTO_TCP;
    _resolveName();
}

void Cataract::IPAddress::_resolveName() {
    struct addrinfo *addrsFound;
    struct addrinfo addrHint = _addrHints;

    if (getaddrinfo(_addr.c_str(), nullptr, &addrHint, &addrsFound) == 0) { // resolving address
        _addr = addrsFound->ai_canonname;
        char tempIp[INET6_ADDRSTRLEN] = {0};
        if (addrHint.ai_family == AF_INET) {
            inet_ntop(addrHint.ai_family, &((struct sockaddr_in *)addrsFound->ai_addr)->sin_addr, tempIp, INET6_ADDRSTRLEN);
        }
        else if (addrHint.ai_family == AF_INET6) {
            inet_ntop(addrHint.ai_family, &((struct sockaddr_in6 *)addrsFound->ai_addr)->sin6_addr, tempIp, INET6_ADDRSTRLEN);
        }
        _ip = tempIp;
        freeaddrinfo(addrsFound);
    }
    else {
        _ip = "ip unknown";
    }
}

void Cataract::IPAddress::setAddr(std::string addr, sa_family_t addrType) {
    _addr = addr;
    _addrHints.ai_flags = AI_CANONNAME;
    _addrHints.ai_family = addrType;
    _addrHints.ai_socktype = SOCK_STREAM;
    _addrHints.ai_protocol = IPPROTO_TCP;
    _resolveName();
}

Cataract::ScanResult::ScanResult(const IPAddress addr, const uint16_t port, const ScanStatus status) {
    _addr = addr;
    _port = port;
    _status = status;
}

uint16_t Cataract::servToPort(std::string service) {
    struct addrinfo *addrsFound;
    struct addrinfo addrHint = {AI_PASSIVE, AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0, 0};

    if (getaddrinfo(nullptr, service.c_str(), &addrHint, &addrsFound) == 0) {
        return ((struct sockaddr_in*)(addrsFound->ai_addr))->sin_port;
    }

    return 80;
}
