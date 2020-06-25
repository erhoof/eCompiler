//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_DO_H
#define ECOMPILER_DO_H

#include "Statement.h"
#include "../Expression.h"

class Do : public Statement {
public:
    Do();

    void init(Statement* s, Expression* x);
    void gen(int b, int a);

    Expression* expr();
    Statement* stmt();

private:
    Expression* m_expr;
    Statement* m_stmt;
};

#endif //ECOMPILER_DO_H
