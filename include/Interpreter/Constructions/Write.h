//
// Created by Pavel Bibichenko on 27.06.2020.
//

#ifndef ECOMPILER_WRITE_H
#define ECOMPILER_WRITE_H

#include "Statement.h"
#include "../Expression.h"

class Write : public Statement {
public:
    explicit Write(Expression* x);

    void gen(int b, int a);

    Expression* m_expr;
};

#endif //ECOMPILER_WRITE_H
