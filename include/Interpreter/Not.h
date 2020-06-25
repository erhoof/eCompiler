//
// Created by Pavel Bibichenko on 21.06.2020.
//

#ifndef ECOMPILER_NOT_H
#define ECOMPILER_NOT_H

#include "Logical.h"

class Not : public Logical {
public:
    Not(Token* token, Expression* x2);

    void jumping(int t, int f);

    std::string toString() const;
};

#endif //ECOMPILER_NOT_H
