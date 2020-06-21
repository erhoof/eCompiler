//
// Created by Pavel Bibichenko on 21.06.2020.
//

#ifndef ECOMPILER_AND_H
#define ECOMPILER_AND_H

#include "Logical.h"

class And : public Logical {
public:
    And(Token& token, Expression* x1, Expression* x2);

    void jumping(int t, int f);
};

#endif //ECOMPILER_AND_H
