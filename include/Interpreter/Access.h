//
// Created by Pavel Bibichenko on 24.06.2020.
//

#ifndef ECOMPILER_ACCESS_H
#define ECOMPILER_ACCESS_H

#include "Operand.h"
#include "Id.h"

class Access : public Operand {
public:
    Access(Id* id, Expression* x, Type* type);

    Id* array() const;
    Expression* index() const;

    Expression* gen();
    void jumping(int t, int f);

    std::string toString();

private:
    Id* m_array;
    Expression* m_index;
};

#endif //ECOMPILER_ACCESS_H
