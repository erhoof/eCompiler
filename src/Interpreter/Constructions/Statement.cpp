//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Statement.h"

Statement* Statement::Null = new Statement();
Statement* Statement::Enclosing = Statement::Null;

int Statement::after() const {
    return m_after;
}

int Statement::setAfter(int after) {
    m_after = after;
    return after;
}

void Statement::gen(int b, int a) {}
