//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_WHILE_H
#define ECOMPILER_WHILE_H

#include "Statement.h"
#include "../Expression.h"

class While : public Statement {
public:
    While();

    void init(Expression* x, Statement* s);
    void gen(int b, int a);

    Expression* expr();
    Statement* stmt();

private:
    Expression* m_expr;
    Statement* m_stmt;
};

#endif //ECOMPILER_WHILE_H
