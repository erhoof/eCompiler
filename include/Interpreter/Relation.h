//
// Created by Pavel Bibichenko on 24.06.2020.
//

#ifndef ECOMPILER_RELATION_H
#define ECOMPILER_RELATION_H

#include "Logical.h"

class Relation : public Logical {
public:
    Relation(Token& token, Expression* x1, Expression* x2);

    Type* check(Type& p1, Type& p2);

    void jumping(int t, int f);
};

#endif //ECOMPILER_RELATION_H
