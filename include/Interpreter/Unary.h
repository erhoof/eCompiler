//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_UNARY_H
#define ECOMPILER_UNARY_H

#include "Operand.h"

class Unary : public Operand {
public:
    Unary(Token& token, Expression& expr);

    Expression* gen();

    std::string toString();

    Expression* expr() const;

private:
    Expression* m_expr;
};

#endif //ECOMPILER_UNARY_H
