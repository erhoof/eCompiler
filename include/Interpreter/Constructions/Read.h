//
// Created by Pavel Bibichenko on 27.06.2020.
//

#ifndef ECOMPILER_READ_H
#define ECOMPILER_READ_H

#include "Statement.h"
#include "../Expression.h"

class Read : public Statement {
public:
    explicit Read(Expression* x);

    void gen(int b, int a);

    Expression* m_expr;
};

#endif //ECOMPILER_READ_H
