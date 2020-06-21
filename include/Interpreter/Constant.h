//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_CONSTANT_H
#define ECOMPILER_CONSTANT_H

#include "Expression.h"

class Constant : public Expression {
public:
    Constant(Token& token, Type& type);
    explicit Constant(int i);

    void jumping(int t, int f);
};

#endif //ECOMPILER_CONSTANT_H
