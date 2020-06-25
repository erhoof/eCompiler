//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Stmt.h"

Stmt* Stmt::Null = new Stmt();
Stmt* Stmt::Enclosing = Stmt::Null;

int Stmt::after() const {
    return m_after;
}

void Stmt::gen(int b, int a) {}
