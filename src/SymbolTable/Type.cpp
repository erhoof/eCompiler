//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/SymbolTable/Type.h"
#include "../../include/SymbolTable/TypeTable.h"

#include <utility>

Type::Type(std::string str, int tag, int width) : Word(std::move(str), tag) {
    m_width = width;
}

int Type::width() const {
    return m_width;
}

bool Type::numeric(Type& p) {
    return (p == *(TypeTable::instance().t_char) ||
            p == *(TypeTable::instance().t_int) ||
            p == *(TypeTable::instance().t_float));
}

Type* Type::max(Type& p1, Type& p2) {
    if (!numeric(p1) || !numeric(p2))
        return nullptr;
    else if (p1 == *(TypeTable::instance().t_float) ||
             p2 == *(TypeTable::instance().t_float))
        return TypeTable::instance().t_float;
    else if (p1 == *(TypeTable::instance().t_int) ||
             p2 == *(TypeTable::instance().t_int))
        return TypeTable::instance().t_int;
    else
        return TypeTable::instance().t_char;
}

bool Type::operator==(const Type& cmp) const {
    return (this->lexeme() == cmp.lexeme());
}
