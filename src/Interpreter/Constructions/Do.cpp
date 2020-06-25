//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Do.h"
#include "../../../include/SymbolTable/TypeTable.h"

Do::Do() {
    m_expr = nullptr;
    m_stmt = nullptr;
}

void Do::init(Statement *s, Expression *x) {
    m_expr = x;
    m_stmt = s;

    if (&expr()->type() != TypeTable::instance().t_bool)
        expr()->error("do expression should have bool expr in it");
}

void Do::gen(int b, int a) {
    m_after = a;

    int label = newLabel(); // expr
    stmt()->gen(b, label);
    emitLabel(label);
    expr()->jumping(b, 0);
}

Expression* Do::expr() {
    return m_expr;
}

Statement* Do::stmt() {
    return m_stmt;
}