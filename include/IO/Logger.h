//
// Created by Pavel Bibichenko on 19.06.2020.
//

#ifndef ECOMPILER_LOGGER_H
#define ECOMPILER_LOGGER_H

#include <string>

class Logger {
public:
    static Logger& instance();

    void log(const std::string& log);
    void log(const std::string& module, const std::string& log);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static std::string string(char c);
private:
    Logger() = default;
};

#endif //ECOMPILER_LOGGER_H
