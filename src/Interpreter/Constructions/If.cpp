//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/If.h"
#include "../../../include/SymbolTable/TypeTable.h"

If::If(Expression* x, Statement* s) {
    m_expr = x;
    m_stmt = s;

    if (&m_expr->type() != TypeTable::instance().t_bool)
        m_expr->error("if expression should have bool expr in it");
}

void If::gen(int b, int a) {
    int label = newLabel();

    m_expr->jumping(0, a);
    emitLabel(label);
    m_stmt->gen(label, a);
}

Expression* If::expr() {
    return m_expr;
}

Statement* If::stmt() {
    return m_stmt;
}