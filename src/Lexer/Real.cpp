//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Real.h"
#include "../../include/Lexer/Tag.h"

Real::Real(float value) : Token(Tag::REAL) {
    m_value = value;
}

float Real::value() const {
    return m_value;
}

std::string Real::toString() const {
    return std::to_string(m_value);
}
