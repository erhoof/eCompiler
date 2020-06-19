//
// Created by Pavel Bibichenko on 19.06.2020.
//

#ifndef ECOMPILER_CORE_H
#define ECOMPILER_CORE_H

#include <string>

class Core{
public:
    static Core& instance();

    int loadFile(const std::string& filename);
    const std::string &inputFile();

    void dumpCore(const std::string& reason);

    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
private:
    Core() = default;

    std::string* m_inputFile;
};

#endif //ECOMPILER_CORE_H
