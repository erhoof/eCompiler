//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Num.h"

#include "../../include/Lexer/Tag.h"

Num::Num(int value) : Token(Tag::NUM) {
    m_value = value;
}

std::string Num::toString() const {
    return std::to_string(m_value);
}

int Num::value() {
    return m_value;
}
