//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Temp.h"
#include "../../include/Lexer/WordTable.h"
#include "../../include/IO/Logger.h"

int Temp::m_count = 0;

Temp::Temp(Type* type) : Expression(WordTable::instance().w_temp, type) {
    m_number = ++m_count;

    Var newVar;
    std::string out = "t";
    out += std::to_string(m_number);
    newVar.name = out;
    newVar.size = type->width();
    Logger::instance().m_vars.push_back(newVar);
}

std::string Temp::toString() const {
    std::string out = "t" + std::to_string(m_number);

    return out;
}
