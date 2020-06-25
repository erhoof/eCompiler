//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_SETELEMENT_H
#define ECOMPILER_SETELEMENT_H

#include "Statement.h"
#include "../Expression.h"
#include "../Id.h"
#include "../Access.h"

class SetElement : public Statement {
public:
    SetElement(Access* x, Expression* y);

    Type* check(Type* t1, Type* t2);
    void gen(int b, int a);

    Id* array();
    Expression* index();
    Expression* expr();

private:
    Id* m_array;
    Expression* m_index;
    Expression* m_expr;
};

#endif //ECOMPILER_SETELEMENT_H
