//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_ARITHMETIC_H
#define ECOMPILER_ARITHMETIC_H

#include "Operand.h"

class Arithmetic : public Operand {
public:
    Arithmetic(Token& token, Expression& x1, Expression& x2);

    Expression* gen();

    std::string toString() const;

    Expression* expr1() const;
    Expression* expr2() const;

private:
    Expression* m_expr1;
    Expression* m_expr2;
};

#endif //ECOMPILER_ARITHMETIC_H
