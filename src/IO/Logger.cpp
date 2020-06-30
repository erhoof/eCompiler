//
// Created by Pavel Bibichenko on 19.06.2020.
//

#include "../../include/IO/Logger.h"
#include "../../include/Core/Core.h"

#include <iostream>
#include <fstream>

Logger &Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::flog(const std::string& log) {
    std::cout << Core::instance().filename() + ":" + log << std::endl;
}

void Logger::log(const std::string& log) {
    std::cout << "itr| " << log << std::endl;
}

void Logger::alog(const std::string& log) {
    if (m_passages) {
        std::cout << "    asm| " << log << std::endl;

        std::ofstream newAsm ("../data/main.asm", std::ios_base::app);
        newAsm << "    " << log << std::endl;
        newAsm.close();
    }
}

void Logger::nalog(const std::string& log) {
    if (m_passages) {
        std::cout << "    asm| " << log << std::endl;

        std::ofstream newAsm ("../data/main.asm", std::ios_base::app);
        newAsm << log << std::endl;
        newAsm.close();
    }
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

void Logger::prepareASM() {
    log("IO", "Preparing ASM file...");

    nalog("section .text");
    alog("global main");
    alog("extern printf");
    alog("");

    // Vars
    std::string out;
    if (!m_vars.empty() || !m_arrays.empty()) {
        nalog("section .bss    ; uninitialized variables");
        for (auto& m_var : m_vars) {
            out = m_var.name;
            out += " resb ";
            out += std::to_string(m_var.size);
            alog(out);
        }
        for (auto& m_arr : m_arrays) {
            out = m_arr.name;
            out += " resb ";
            out += std::to_string(m_arr.width * m_arr.size);
            alog(out);
        }
    }

    // Lines
    nalog("section .data    ; strings and other big stuff");
    for (int i = 0; i < m_lines.size(); i++) {
        out = "line";
        out += std::to_string(i);
        out += " db '";
        out += m_lines[i];
        out += '\'';
        alog(out);

        out = "lenLine";
        out += std::to_string(i);
        out += " equ $-";
        out += "line";
        out += std::to_string(i);
        alog(out);
    }
    alog("fmtd db '%d', 10, 0"); // Integer
    alog("fmtf db '%f', 10, 0"); // Float
    alog("fmtc db '%c', 10, 0"); // Char
    alog("fmtb db '%d', 10, 0"); // Bool
    alog("");

    nalog("main:");
}

void Logger::finishASM() {

    // Add Return code
    alog("mov eax, 1");
    alog("mov ebx, 0");
    alog("int 80h");
}

int Logger::getLineNumb() {
    static int lines = 0;

    return lines++;
}