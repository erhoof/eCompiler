//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Break.h"
#include "../../../include/IO/Logger.h"

Break::Break() {
    if (Statement::Enclosing == nullptr)
        error("unenclosed break");

    m_stmt = Statement::Enclosing;
}

void Break::gen(int b, int a) {
    std::string out = "goto L" + std::to_string(m_stmt->after());
    std::string aout = "jmp L" + std::to_string(m_stmt->after());

    emit(out);
}

Statement* Break::stmt() {
    return m_stmt;
}
