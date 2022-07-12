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
