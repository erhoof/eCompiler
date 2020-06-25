//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Sequence.h"

Sequence::Sequence(Statement* s1, Statement* s2) {
    m_stmt1 = s1;
    m_stmt2 = s2;
}

void Sequence::gen(int b, int a) {
    if (stmt1() == Statement::Null) {
        m_stmt2->gen(b, a);
    } else if (stmt2() == Statement::Null)
        m_stmt1->gen(b, a);
    else {
        int label = newLabel();
        stmt1()->gen(b, label);
        emitLabel(label);
        stmt2()->gen(label, a);
    }
}

Statement* Sequence::stmt1() {
    return m_stmt1;
}

Statement* Sequence::stmt2() {
    return m_stmt2;
}
