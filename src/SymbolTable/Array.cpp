//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/SymbolTable/Array.h"
#include "../../include/Lexer/Tag.h"

Array::Array(int size, Type& type) : Type("[]", Tag::INDEX, size*(type.width())) {
    m_size = size;
    m_type = &type;
}

std::string Array::toString() {
    std::string out = "[" + std::to_string(m_size) + "] " + m_type->toString();
}

Type* Array::type() const {
    return m_type;
}

int Array::size() const {
    return m_size;
}
