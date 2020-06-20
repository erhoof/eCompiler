//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_OPERAND_H
#define ECOMPILER_OPERAND_H

#include "Expression.h"

class Operand : public Expression {
public:
    Operand(Token& token, Type& type);
    Expression& reduce();
};

#endif //ECOMPILER_OPERAND_H
