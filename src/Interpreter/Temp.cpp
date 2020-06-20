//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Temp.h"
#include "../../include/Lexer/WordTable.h"

int Temp::m_count = 0;

Temp::Temp(Type& type) : Expression(*WordTable::instance().w_temp, type) {
    m_number = ++m_count;
}

std::string Temp::toString() const {
    std::string out = "t" + std::to_string(m_number);

    return out;
}
