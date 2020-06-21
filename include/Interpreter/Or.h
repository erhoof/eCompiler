//
// Created by Pavel Bibichenko on 21.06.2020.
//

#ifndef ECOMPILER_OR_H
#define ECOMPILER_OR_H

#include "Logical.h"

class Or : public Logical {
public:
    Or(Token& token, Expression* x1, Expression* x2);
    void jumping(int t, int f);
};

#endif //ECOMPILER_OR_H
