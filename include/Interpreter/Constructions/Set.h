//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_SET_H
#define ECOMPILER_SET_H

#include "Statement.h"
#include "../Id.h"

class Set : public Statement {
public:
    Set(Id* id, Expression* x);

    Type* check(Type* t1, Type* t2);
    void gen(int b, int a);

    Id* id();
    Expression* expr();

private:
    Id* m_id;
    Expression* m_expr;
};

#endif //ECOMPILER_SET_H
