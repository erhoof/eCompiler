//
// Created by Pavel Bibichenko on 19.06.2020.
//

#ifndef ECOMPILER_LOGGER_H
#define ECOMPILER_LOGGER_H

#include <string>
#include <vector>

struct Var {
    std::string name;
    int size;
};

struct PreArray {
    std::string name;
    int size;
    int width;
};

class Logger {
public:
    static Logger& instance();

    void log(const std::string& log);
    void nalog(const std::string& log);
    void alog(const std::string& log);
    void nlog(const std::string& log);
    void flog(const std::string& log);
    void log(const std::string& module, const std::string& log);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::vector<std::string> m_lines;
    int getLineNumb();
    std::vector<Var> m_vars;
    std::vector<PreArray> m_arrays;

    int m_passages = 0;
    void prepareASM();
    void finishASM();

    static std::string string(char c);
private:
    Logger() = default;
};

#endif //ECOMPILER_LOGGER_H
