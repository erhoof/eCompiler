//
// Created by Pavel Bibichenko on 19.06.2020.
//

#include "../../include/IO/Logger.h"
#include "../../include/Core/Core.h"

#include <iostream>

Logger &Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::flog(const std::string& log) {
    std::cout << Core::instance().filename() + ":" + log << std::endl;
}

void Logger::log(const std::string& log) {
    std::cout << log << std::endl;
}

void Logger::alog(const std::string& log) {
    std::cout << "asm| " << log << std::endl;
}

void Logger::nlog(const std::string& log) {
    std::cout << log;
}

void Logger::log(const std::string &module, const std::string &log) {
    std::cout << "[" << module << "]: " << log << std::endl;
}

std::string Logger::string(char c) {
    std::string str(1, c);

    return str;
}