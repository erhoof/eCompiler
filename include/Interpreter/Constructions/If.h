//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_IF_H
#define ECOMPILER_IF_H

#include "Statement.h"
#include "../Expression.h"

class If : public Statement {
public:
    If(Expression* x, Statement* s);

    void gen(int b, int a);

private:
    Expression* m_expr;
    Statement* m_stmt;
};

#endif //ECOMPILER_IF_H
