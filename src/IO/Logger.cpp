//
// Created by Pavel Bibichenko on 19.06.2020.
//

#include "../../include/IO/Logger.h"

#include <iostream>

Logger &Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string& log) {
    std::cout << log << std::endl;
}
