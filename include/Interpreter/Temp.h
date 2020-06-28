//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_TEMP_H
#define ECOMPILER_TEMP_H

#include "Expression.h"

class Temp : public Expression {
public:
    explicit Temp(Type* type);
    std::string toString() const;

    static int m_count;

private:
    int m_number;
};

#endif //ECOMPILER_TEMP_H
