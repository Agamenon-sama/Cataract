#define SLOG_IMPLEMENTATION
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Cataract/Cataract.h"

#include "utils.h"

#include <slog/slog.h>

#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }

    if (argc != 5) {
        slog::error("Invalid arguments");
        slog::info("Usage example : cataract ports 45-78,5,8 host localhost");
        slog::info("Usage example : cataract ports 45-78,5,8 host6 ::1");
        return 1;
    }

    // holds address of the host to be scanned
    Cataract::IPAddress addr;
    // holds ports
    std::vector<uint16_t> ports;

    // Argument parsing phase
    for (int argCount = 1; argCount < argc; argCount++) {
        if (std::string(argv[argCount]) == "ports") {
            // get comma Separated ranges
            argCount++;
            if (argCount >= argc) {
                slog::error("Argument missing");
                return 1;
            }

            if(!argToPorts(argv[argCount], ports)) {
                slog::error("The ports ranges you inputed are invalid");
                return 2;
            }
            /* auto commaSeparated = splitLine(argv[argCount], ',');
            

            for (auto strRange : commaSeparated) {
                // get limits of range
                auto tempRange = splitLine(strRange, '-');
                // turn range to std::pair
                std::pair<uint16_t, uint16_t> range;

                if (tempRange.size() == 1) {
                    // if it's a single port number we set the other limit to 0
                    try {
                        range = {std::stoi(tempRange[0]), 0};
                    }
                    catch(std::exception &e) {
                        slog::error("Invalid port number");
                        return 2;
                    }
                } else {
                    // if it's a range we set the limits to the given numbers
                    if (tempRange.size() > 2) {
                        slog::warning("There is an invalid range\n"
                            "Port ranges should look like : x-y\n"
                            "only the first and second ranges will be considered");
                    }
                    try {
                        range = {std::stoi(tempRange[0]), std::stoi(tempRange[1])};
                    }
                    catch(std::exception &e) {
                        slog::error("Invalid port number");
                        return 2;
                    }
                }
                ranges.push_back(range);
            }*/
        }
        else if (std::string(argv[argCount]) == "host") {
            argCount++;
            if (argCount >= argc) {
                slog::error("Argument missing after \"host\"");
                return 1;
            }
            addr.setAddr(argv[argCount]);
        }
        else if (std::string(argv[argCount]) == "host6") {
            argCount++;
            if (argCount >= argc) {
                slog::error("Argument missing after \"host6\"");
                return 1;
            }
            addr.setAddr(argv[argCount], AF_INET6);
        }
        else {
            std::string warningMessage = "Invalid argument ";
            warningMessage += argv[argCount];
            slog::warning(warningMessage);
        }
        
    }

    // Scanning phase
    Cataract::TcpScanner scanner;
    
    /* for(auto range : ranges) {
        if(range.second == 0) {
            // if it's a single port we push it as it is
            ports.push_back(range.first);
        }
        else {
            if (range.first > range.second) {
                slog::warning("the port ranges are in the wrong sense");
                std::swap(range.first, range.second);
            }
            // else we fill all the ports in the range
            for(int i = range.first; i <= range.second; i++) {
                ports.push_back(i);
            }
        }
    } */
    // We scan and print the results
    auto scanResult = scanner.portSweep(addr, ports);
    for(auto test : scanResult) {
        if(test.isOpen()) { // second holds the test result
            std::cout << "Port " << test.getPort() << "/tcp is \e[32mopen\e[0m\n";
        } else {
            std::cout << "Port " << test.getPort() << "/tcp is \e[31mclosed\e[0m\n";
        }
    }

    return 0;
}
