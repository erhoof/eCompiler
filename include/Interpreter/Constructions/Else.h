//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_ELSE_H
#define ECOMPILER_ELSE_H

#include "Statement.h"
#include "../Expression.h"

class Else : public Statement {
public:
    Else(Expression* x, Statement* s1, Statement* s2);

    void gen(int b, int a);

    Expression* expr();
    Statement* stmt1();
    Statement* stmt2();

private:
    Expression* m_expr;
    Statement* m_stmt1;
    Statement* m_stmt2;
};

#endif //ECOMPILER_ELSE_H
