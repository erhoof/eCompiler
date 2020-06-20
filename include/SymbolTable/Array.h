//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_ARRAY_H
#define ECOMPILER_ARRAY_H

#include "Type.h"

class Array : public Type {
public:
    Array(int size, Type& type);

    std::string toString();

    Type* type() const;
    int size() const;

private:
    Type* m_type;
    int m_size = 1;
};

#endif //ECOMPILER_ARRAY_H
