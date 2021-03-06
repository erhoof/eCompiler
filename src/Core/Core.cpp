//
// Created by Pavel Bibichenko on 19.06.2020.
//

#include "../../include/Core/Core.h"
#include "../../include/IO/Logger.h"
#include "../../include/Lexer/Lexer.h"
#include "../../include/Parser/Parser.h"

#include <fstream>
#include <streambuf>

Core &Core::instance() {
    static Core core;

    return core;
}

int Core::loadFile(const std::string &filename) {
    Logger::instance().log("Core", "loading file " + filename);

    std::ifstream stream(filename);
    m_fileName = filename;

    if (stream) {
        Logger::instance().log("Core", "file successfully loaded!");

        m_inputFile = new std::string((std::istreambuf_iterator<char>(stream)),
                                      std::istreambuf_iterator<char>());

        return 0;
    } else {
        Logger::instance().log("Core", "couldn't load the file");

        dumpCore("input file was not provided.");

        return 1;
    }
}

const std::string &Core::inputFile() {
    return *m_inputFile;
}

char Core::nextChar() {
    char ch = m_inputFile->c_str()[m_charNumb];
    m_charNumb++;

    //Logger::instance().log("Core", "nextChar: " + Logger::string(ch));

    return ch;
}

void Core::dumpCore(const std::string &reason) {
    Logger::instance().log("\nFATAL ERROR: " + reason);
    Logger::instance().log("dumping the core...");

    std::exit(1);
}

void Core::process() {
    auto lexer = new Lexer();
    auto parser = new Parser(lexer);
    parser->program();
}

std::string Core::filename() const {
    return m_fileName;
}