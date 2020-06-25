//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_ID_H
#define ECOMPILER_ID_H

#include "Expression.h"

class Id : public Expression {
public:
    Id(Word* id, Type* type, int offset);

    int offset() const;

private:
    int m_offset;
};

#endif //ECOMPILER_ID_H
