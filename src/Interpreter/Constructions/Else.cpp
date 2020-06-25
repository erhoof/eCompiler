//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Else.h"
#include "../../../include/SymbolTable/TypeTable.h"

Else::Else(Expression *x, Statement *s1, Statement *s2) {
    m_expr = x;
    m_stmt1 = s1;
    m_stmt2 = s2;

    if (&expr()->type() == TypeTable::instance().t_bool)
        expr()->error("if expression should have bool expr in it");
}

void Else::gen(int b, int a) {
    int label1 = newLabel(); // statement 1 label
    int label2 = newLabel(); // statement 2 label

    expr()->jumping(0, label2); // if true -> statement 2

    emitLabel(label1);
    stmt1()->gen(label1, a);
    emit("goto L" + std::to_string(a));
    emitLabel(label2);
    stmt2()->gen(label2, a);
}

Expression *Else::expr() {
    return m_expr;
}

Statement *Else::stmt1() {
    return m_stmt1;
}

Statement *Else::stmt2() {
    return m_stmt2;
}
