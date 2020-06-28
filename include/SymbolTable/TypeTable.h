//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_TYPETABLE_H
#define ECOMPILER_TYPETABLE_H

#include "Type.h"

class TypeTable {
public:
    static TypeTable& instance();

    TypeTable(const TypeTable&) = delete;
    TypeTable& operator=(const TypeTable&) = delete;

    // Type Table
    Type* t_int;
    Type* t_float;
    Type* t_char;
    Type* t_bool;
    Type* t_str;
private:
    TypeTable();
};

#endif //ECOMPILER_TYPETABLE_H
