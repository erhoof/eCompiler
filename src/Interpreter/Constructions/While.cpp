//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/While.h"
#include "../../../include/SymbolTable/TypeTable.h"

While::While() {
    m_expr = nullptr;
    m_stmt = nullptr;
}

void While::init(Expression *x, Statement *s) {
    m_expr = x;
    m_stmt = s;

    if (&m_expr->type() != TypeTable::instance().t_bool)
        m_expr->error("while expression should have bool expr in it");
}

void While::gen(int b, int a) {
    m_after = a;

    expr()->jumping(0, a);

    int label = newLabel(); // stmt
    emitLabel(label);
    stmt()->gen(label, b);
    emit("goto L" + std::to_string(b));
}

Expression* While::expr() {
    return m_expr;
}

Statement* While::stmt() {
    return m_stmt;
}