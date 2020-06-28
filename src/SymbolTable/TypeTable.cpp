//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/SymbolTable/TypeTable.h"
#include "../../include/Lexer/Tag.h"

TypeTable &TypeTable::instance() {
    static TypeTable TypeTable;
    return TypeTable;
}

TypeTable::TypeTable() {
    t_int = new Type("int",     Tag::BASIC, 4);
    t_float = new Type("float", Tag::BASIC, 8);
    t_char = new Type("char",   Tag::BASIC, 1);
    t_bool = new Type("bool",   Tag::BASIC, 1);
    t_str = new Type("string",  Tag::BASIC, 0);
}