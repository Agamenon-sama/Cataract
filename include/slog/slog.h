#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>

namespace slog {
    enum class Decorator {
        Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White, Default = 39
    };

    class Logger {
        public:
            Logger() {
                _decorator = Decorator::Default;
                _prefix = "";
                _displayTime = false;
                _outputFile = "stdout";
            }
        
            void setPrefix(std::string prefix) { _prefix = prefix; }
            void setDecorator(Decorator decorator) { _decorator = decorator; }
            void displayTime(bool val) { _displayTime = val; }
            void setOutputFile(std::string filename) { _outputFile = filename; }

            void operator()(std::string message) {
                _print(_createPrintable(message));
            }
        protected:
            std::string _prefix;
            Decorator _decorator;
            bool _displayTime;
            std::string _outputFile;

            std::string _createPrintable(std::string message) {
                // create time string
                std::string timeStr = "";
                if(_displayTime) {
                    time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    timeStr = ctime(&time);
                    timeStr = timeStr.substr(11, 8);
                    timeStr += " == ";
                }

                std::string decoPrefix = "", decoSuffix = "";
                if(_outputFile == "stdout" || _outputFile == "stderr") {
                    decoPrefix = "\e[";
                    decoPrefix += std::to_string((int)_decorator);
                    decoPrefix += "m";
                    decoSuffix = "\e[0m";
                }
                
                return decoPrefix + timeStr + _prefix + message + decoSuffix;
            }

            void _print(std::string message) {
                if(_outputFile == "stdout") {
                    printf("%s\n", message.c_str());
                    // printf("\e[%dm%s%s%s\n\e[0m", (int)_decorator, timeStr.c_str(), _prefix.c_str(), message.c_str());
                } else if(_outputFile == "stderr") {
                    fprintf(stderr, "%s\n", message.c_str());
                    // fprintf(stderr, "\e[%dm%s%s%s\n\e[0m", (int)_decorator, timeStr.c_str(), _prefix.c_str(), message.c_str());
                } else {
                    FILE *file = fopen(_outputFile.c_str(), "a");
                    if(file) {
                        fprintf(file, "%s\n", message.c_str());
                        // fprintf(file, "\e[%dm%s%s%s\n\e[0m", (int)_decorator, timeStr.c_str(), _prefix.c_str(), message.c_str());
                        fclose(file);
                    }
                }
            }
    };

    class Error : public Logger {
        public:
            Error() : Logger() {
                _prefix = "Error : ";
                _decorator = Decorator::Red;
                _outputFile = "stderr";
            }
    };

    class Warning : public Logger {
        public:
            Warning() : Logger() {
                _prefix = "Warning : ";
                _decorator = Decorator::Yellow;
                _outputFile = "stderr";
            }
    };

    class Info : public Logger {
        public:
            Info() : Logger() {
                _prefix = "Info : ";
                _decorator = Decorator::Blue;
            }
    };

    extern Error error;
    extern Warning warning;
    extern Info info;
    extern Logger message;

    // Make sure to define SLOG_IMPLEMENTATION in one of your source files
#ifdef SLOG_IMPLEMENTATION
    Error error;
    Warning warning;
    Info info;
    Logger message;
#endif // SLOG_IMPLEMENTATION
}
