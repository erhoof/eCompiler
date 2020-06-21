//
// Created by Pavel Bibichenko on 21.06.2020.
//

#ifndef ECOMPILER_LOGICAL_H
#define ECOMPILER_LOGICAL_H

#include "Expression.h"

class Logical : public Expression {
public:
    Logical(Token& token, Expression* x1, Expression* x2);

    Type* check(Type& p1, Type& p2) const;
    Expression* gen();

    std::string toString() const;

    Expression* expr1() const;
    Expression* expr2() const;

private:
    Expression* m_expr1;
    Expression* m_expr2;
};

#endif //ECOMPILER_LOGICAL_H
