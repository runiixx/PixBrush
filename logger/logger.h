//
// Created by vik on 7/2/25.
//

#ifndef LOGGER_H
#define LOGGER_H
#define LOGGER_INFO "\033[32m"
#define LOGGER_WARNING "\033[33m"
#define LOGGER_ERROR "\033[31m"
#define RESET "\033[0m"

#include <ctime>
#include <iostream>

//TODO: maybe rewrite this
namespace logger {
    template<typename... Args>
void info(const char *format, Args... args) {
        std::time_t t = std::time(nullptr);
        char buff[100];
        std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        std::cout << "[" << buff << "] [" << LOGGER_INFO << "INFO" << RESET << "] ";
        std::printf(format, args...);
        std::cout <<'\n';
    }

    template<typename... Args>
    void warning(const char *format, Args... args) {
        std::time_t t = std::time(nullptr);
        char buff[100];
        std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        std::cout << "[" << buff << "] [" << LOGGER_WARNING << "INFO" << RESET << "] ";
        std::printf(format, args...);
        std::cout <<'\n';
    }

    template<typename... Args>
    void error(const char *format, Args... args) {
        std::time_t t = std::time(nullptr);
        char buff[100];
        std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        std::cout << "[" << buff << "] [" << LOGGER_ERROR << "INFO" << RESET << "] ";
        std::printf(format, args...);
        std::cout <<'\n';
    }
}
#endif //LOGGER_H
