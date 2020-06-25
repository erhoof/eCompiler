//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_SEQUENCE_H
#define ECOMPILER_SEQUENCE_H

#include "Statement.h"

class Sequence : public Statement {
public:
    Sequence(Statement* s1, Statement* s2);

    void gen(int b, int a);

    Statement* stmt1();
    Statement* stmt2();

private:
    Statement* m_stmt1;
    Statement* m_stmt2;
};

#endif //ECOMPILER_SEQUENCE_H
